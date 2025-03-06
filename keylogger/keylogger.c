#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>
#include <ctype.h>

// Lista de processos do sistema que devem ser ignorados
const char *system_processes[] = {
    "svchost.exe",
    "winlogon.exe",
    "services.exe",
    "system",
    "smss.exe",
    "csrss.exe",
    "wininit.exe",
    "lsass.exe"
};

// Assinaturas conhecidas de keyloggers
const char *keylogger_signatures[] = {
    "keylogger",
    "keystroke",
    "keylog",
    "winlogger",
    "keyspy",
    "keysniff",
    "keytrack",
    "hookkeyboard",
    "keycapture",
    "keysniffer"
};

// Função para converter string para minúsculas
void to_lower(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Função para obter o nome do executável atual
void get_current_exe_name(char *buffer, size_t size) {
    GetModuleFileName(NULL, buffer, size);
    char *last_slash = strrchr(buffer, '\\');
    if (last_slash != NULL) {
        strncpy(buffer, last_slash + 1, size);
        buffer[size - 1] = '\0';
    }
}

// Função para verificar se é um processo do sistema
int is_system_process(const char *process_name) {
    char process_lower[MAX_PATH];
    char system_lower[MAX_PATH];
    
    strncpy(process_lower, process_name, MAX_PATH - 1);
    process_lower[MAX_PATH - 1] = '\0';
    to_lower(process_lower);
    
    for (int i = 0; i < sizeof(system_processes) / sizeof(system_processes[0]); ++i) {
        strncpy(system_lower, system_processes[i], MAX_PATH - 1);
        system_lower[MAX_PATH - 1] = '\0';
        to_lower(system_lower);
        
        if (strcmp(process_lower, system_lower) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para verificar keyloggers rodando no sistema
int check_for_keyloggers() {
    SetConsoleOutputCP(65001); // Configura o console para UTF-8
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    int keyloggers_found = 0;
    char current_exe[MAX_PATH];

    // Obtém o nome do executável atual
    get_current_exe_name(current_exe, MAX_PATH);

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("Erro: Não foi possível criar o snapshot dos processos.\n");
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        printf("Erro ao obter informações do primeiro processo.\n");
        CloseHandle(hProcessSnap);
        return 1;
    }

    printf("\n🔍 Iniciando varredura do sistema...\n");
    printf("----------------------------------------\n");

    do {
        // Ignora o próprio executável e processos do sistema
        if (strcmp(pe32.szExeFile, current_exe) == 0 || is_system_process(pe32.szExeFile)) {
            continue;
        }

        // Converte o nome do processo para minúsculas para comparação
        char process_name[MAX_PATH];
        strncpy(process_name, pe32.szExeFile, MAX_PATH - 1);
        process_name[MAX_PATH - 1] = '\0';
        to_lower(process_name);

        for (int i = 0; i < sizeof(keylogger_signatures) / sizeof(keylogger_signatures[0]); ++i) {
            char signature[MAX_PATH];
            strncpy(signature, keylogger_signatures[i], MAX_PATH - 1);
            signature[MAX_PATH - 1] = '\0';
            to_lower(signature);
            
            if (strstr(process_name, signature) != NULL) {
                printf("⚠️  Processo suspeito detectado:\n");
                printf("   - Nome: %s\n", pe32.szExeFile);
                printf("   - PID: %lu\n", pe32.th32ProcessID);
                printf("   - Threads: %lu\n", pe32.cntThreads);
                printf("   - Prioridade: %lu\n", pe32.pcPriClassBase);
                printf("----------------------------------------\n");
                keyloggers_found++;
                break;
            }
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return keyloggers_found;
}

int main() {
    SetConsoleTitle("Scanner de Processos Suspeitos");
    printf("🛡️  Scanner de Processos Suspeitos v1.0\n");
    printf("----------------------------------------\n");
    
    int keyloggers_found = check_for_keyloggers();

    if (keyloggers_found == 0) {
        printf("✅ Nenhum processo suspeito detectado.\n");
    } else {
        printf("⚠️  Total de processos suspeitos detectados: %d\n", keyloggers_found);
        printf("⚠️  Recomenda-se investigar estes processos manualmente.\n");
        printf("💡 Dica: Use o Gerenciador de Tarefas (Task Manager) para mais detalhes.\n");
    }

    return 0;
}