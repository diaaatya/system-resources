#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

WINBASEAPI BOOL WINAPI GetSystemTimes(
    LPFILETIME lpIdleTime,
    LPFILETIME lpKernelTime,
    LPFILETIME lpUserTime
);

#ifdef __cplusplus
}
#endif
#include <stdio.h>

void get_cpu_usage(double *cpu_usage) {
    static FILETIME prev_idle_time = {0, 0}, prev_kernel_time = {0, 0}, prev_user_time = {0, 0};

    FILETIME idle_time, kernel_time, user_time;
    if (GetSystemTimes(&idle_time, &kernel_time, &user_time) == 0) {
        printf("Failed to get CPU usage.\n");
        *cpu_usage = -1.0; // Indicate an error
        return;
    }

    // Convert FILETIME to ULARGE_INTEGER for calculation
    ULARGE_INTEGER idle, kernel, user;
    ULARGE_INTEGER prev_idle, prev_kernel, prev_user;

    idle.LowPart = idle_time.dwLowDateTime;
    idle.HighPart = idle_time.dwHighDateTime;

    kernel.LowPart = kernel_time.dwLowDateTime;
    kernel.HighPart = kernel_time.dwHighDateTime;

    user.LowPart = user_time.dwLowDateTime;
    user.HighPart = user_time.dwHighDateTime;

    prev_idle.LowPart = prev_idle_time.dwLowDateTime;
    prev_idle.HighPart = prev_idle_time.dwHighDateTime;

    prev_kernel.LowPart = prev_kernel_time.dwLowDateTime;
    prev_kernel.HighPart = prev_kernel_time.dwHighDateTime;

    prev_user.LowPart = prev_user_time.dwLowDateTime;
    prev_user.HighPart = prev_user_time.dwHighDateTime;

    // Calculate deltas
    ULONGLONG delta_idle = idle.QuadPart - prev_idle.QuadPart;
    ULONGLONG delta_kernel = kernel.QuadPart - prev_kernel.QuadPart;
    ULONGLONG delta_user = user.QuadPart - prev_user.QuadPart;

    // Save current values for next calculation
    prev_idle_time = idle_time;
    prev_kernel_time = kernel_time;
    prev_user_time = user_time;

    // Total time = kernel + user - idle
    ULONGLONG delta_total = delta_kernel + delta_user;
    if (delta_total > 0) {
        *cpu_usage = 100.0 * (1.0 - (double)delta_idle / delta_total);
    } else {
        *cpu_usage = 0.0; // If delta_total is 0, assume no CPU usage
    }
}

void get_memory_usage(double *mem_usage) {
    MEMORYSTATUSEX mem_status;
    mem_status.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&mem_status)) {
        DWORDLONG total_physical = mem_status.ullTotalPhys;
        DWORDLONG used_physical = total_physical - mem_status.ullAvailPhys;

        *mem_usage = 100.0 * (double)used_physical / total_physical;
    } else {
        *mem_usage = -1.0; // Indicate an error
    }
}

int main() {
    printf("Real-Time System Resource Monitor (Windows) By Diaa Atya\n");
    printf("-------------------------------------------\n");
    printf("| %-10s | %-10s |\n", "CPU Usage", "Memory Usage");
    printf("-------------------------------------------\n");

    while (1) {
        double cpu_usage = 0.0, mem_usage = 0.0;

        get_cpu_usage(&cpu_usage);
        get_memory_usage(&mem_usage);

        if (cpu_usage >= 0.0 && mem_usage >= 0.0) {
            // Move the cursor back to the beginning of the line and overwrite the previous line
            printf("\r| %-10.2f%% | %-10.2f%% |", cpu_usage, mem_usage);
        } else {
            printf("\r| %-10s | %-10s |", "Error", "Error");
        }

        // Refresh the line after printing the new values
        fflush(stdout);
        Sleep(1000); // Update every second
        
    }

    return 0;
}
