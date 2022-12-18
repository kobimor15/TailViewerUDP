#include "TailViewerService.h"

/****************************** Module Header ******************************\
* Module Name:  TailViewerService.cpp
* Project:      Service-TailViewer
* Copyright (c) Microsoft Corporation.
* Copyright (c) Tromgy (tromgy@yahoo.com)
*
* Provides a TailViewer server service class that derives from the service base class -
* CServiceBase. The TailViewer server service logs the service start and stop
* information to the Application event log, and shows how to run the main
* function of the service in a thread pool worker thread.
*
* This source is subject to the Microsoft Public License.
* See http://www.microsoft.com/en-us/openness/resources/licenses.aspx#MPL.
* All other rights reserved.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
\***************************************************************************/

#include "stdafx.h"
#include "TailViewerService.h"
#include "event_ids.h"

// ------------------------------------------
#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1;
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
using namespace udp;

TailViewerService::TailViewerService(PCWSTR pszServiceName,
    BOOL fCanStop,
    BOOL fCanShutdown,
    BOOL fCanPauseContinue) :
    CServiceBase(pszServiceName, fCanStop, fCanShutdown, fCanPauseContinue, MSG_SVC_FAILURE, CATEGORY_SERVICE)
{
    m_bIsStopping = FALSE;

    m_hHasStoppedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (m_hHasStoppedEvent == NULL)
    {
        throw GetLastError();
    }
}

void TailViewerService::OnStart(DWORD /* useleses */, PWSTR* /* useless */)
{
    const wchar_t* wsConfigFullPath = SERVICE_CONFIG_FILE;
    bool bRunAsService = true;

    // Log a service start message to the Application log.
    WriteLogEntry(L"TailViewer Server Service is starting...", EVENTLOG_INFORMATION_TYPE, MSG_STARTUP, CATEGORY_SERVICE);

    if (m_argc > 1)
    {
        bRunAsService = (_wcsicmp(SERVICE_CMD, m_argv[1]) == 0);

        // Check if the config file was specified on the service command line
        if (m_argc > 2) // the argument at 1 should be "run mode", so we start at 2
        {
            if (_wcsicmp(L"-config", m_argv[2]) == 0)
            {
                if (m_argc > 3)
                {
                    wsConfigFullPath = m_argv[3];
                }
                else
                {
                    throw exception("no configuration file name");
                }
            }
        }
    }
    else
    {
        WriteLogEntry(L"TailViewer Server Service:\nNo run mode specified.", EVENTLOG_ERROR_TYPE, MSG_STARTUP, CATEGORY_SERVICE);
        throw exception("no run mode specified");
    }

    try
    {
        // Here we would load configuration file
        // but instead we're just writing to event log the configuration file name
        wstring infoMsg = L"TailViewer Server Service\n The service is pretending to read configuration from ";
        infoMsg += wsConfigFullPath;
        WriteLogEntry(infoMsg.c_str(), EVENTLOG_INFORMATION_TYPE, MSG_STARTUP, CATEGORY_SERVICE);
    }
    catch (exception const& e)
    {
        WCHAR wszMsg[MAX_PATH];

        _snwprintf_s(wszMsg, _countof(wszMsg), _TRUNCATE, L"TailViewer Server Service\nError reading configuration %S", e.what());

        WriteLogEntry(wszMsg, EVENTLOG_ERROR_TYPE, MSG_STARTUP, CATEGORY_SERVICE);
    }

    if (bRunAsService)
    {
        WriteLogEntry(L"TailViewer Server will run as a service.", EVENTLOG_INFORMATION_TYPE, MSG_STARTUP, CATEGORY_SERVICE);

        // Add the main service function for execution in a worker thread.
        if (!CreateThread(NULL, 0, ServiceRunner, this, 0, NULL))
        {
            WriteLogEntry(L"TailViewer Server Service couldn't create worker thread.", EVENTLOG_ERROR_TYPE, MSG_STARTUP, CATEGORY_SERVICE);
        }
    }
    else
    {
        wprintf(L"TailViewer Server Service is running as a regular process.\n");

        TailViewerService::ServiceRunner(this);
    }
}

TailViewerService::~TailViewerService()
{
}

void TailViewerService::Run()
{
    OnStart(0, NULL);
}

// The static method:
DWORD __stdcall TailViewerService::ServiceRunner(void* self)
{
    TailViewerService* pService = (TailViewerService*)self;

    pService->WriteLogEntry(L"TailViewer Server Service has started.", EVENTLOG_INFORMATION_TYPE, MSG_STARTUP, CATEGORY_SERVICE);

    // Periodically check if the service is stopping.
    for (bool once = true; !pService->m_bIsStopping; once = false)
    {
        if (once)
        {
            // Log multi-line message
            pService->WriteLogEntry(L"TailViewerService Service is running...\n", EVENTLOG_INFORMATION_TYPE, MSG_OPERATION, CATEGORY_SERVICE);
        }
        TailViewerUDPServer::runTailViewerServer();
    }

    // Signal the stopped event.
    SetEvent(pService->m_hHasStoppedEvent);
    pService->WriteLogEntry(L"TailViewer Server Service has stopped.", EVENTLOG_INFORMATION_TYPE, MSG_SHUTDOWN, CATEGORY_SERVICE);

    return 0;
}

void TailViewerService::OnStop()
{
    // Log a service stop message to the Application log.
    WriteLogEntry(L"TailViewer Server Service is stopping", EVENTLOG_INFORMATION_TYPE, MSG_SHUTDOWN, CATEGORY_SERVICE);

    // Indicate that the service is stopping and wait for the finish of the
    // main service function (ServiceWorkerThread).
    m_bIsStopping = TRUE;

    if (WaitForSingleObject(m_hHasStoppedEvent, INFINITE) != WAIT_OBJECT_0)
    {
        throw GetLastError();
    }
}
