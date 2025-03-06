# 🛡️ Scanner de Processos Suspeitos

Um programa em C para detectar possíveis keyloggers e outros processos suspeitos rodando no sistema Windows.

## 📋 Características

- Detecção de processos potencialmente maliciosos
- Interface amigável com emojis e formatação clara
- Análise em tempo real dos processos em execução
- Detecção case-insensitive para maior precisão
- Filtragem inteligente de processos do sistema
- Exibição detalhada de informações dos processos suspeitos

## 🚀 Como Usar

### Pré-requisitos

- Sistema operacional Windows
- GCC (MinGW) instalado
- Git (opcional, para clonar o repositório)

### Compilação

1. Clone o repositório ou baixe o código fonte
```bash
git clone https://seu-repositorio/scanner-processos.git
cd scanner-processos
```

2. Compile o programa
```bash
gcc keylogger.c -o scanner.exe
```

3. Execute o programa
```bash
./scanner.exe
```

## 📊 Informações Exibidas

Para cada processo suspeito detectado, o programa mostra:
- Nome do processo
- PID (Process ID)
- Número de threads
- Prioridade do processo

## 🔍 Como Funciona

O programa utiliza as APIs do Windows para:
1. Criar um snapshot dos processos em execução
2. Analisar cada processo comparando com assinaturas conhecidas
3. Filtrar processos legítimos do sistema
4. Exibir informações detalhadas dos processos suspeitos

## ⚠️ Observações

- Este é um programa de detecção simples e pode gerar falsos positivos
- Recomenda-se investigar manualmente os processos detectados
- O programa não remove nem modifica nenhum processo
- Use em conjunto com outras ferramentas de segurança

## 🛠️ Tecnologias Utilizadas

- Linguagem C
- APIs do Windows (windows.h, tlhelp32.h)
- Biblioteca padrão C

## 📝 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 🤝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para:
- Reportar bugs
- Sugerir novas funcionalidades
- Melhorar a documentação
- Enviar pull requests

## 🔄 Atualizações Futuras Planejadas

- [ ] Adicionar mais assinaturas de processos suspeitos
- [ ] Implementar análise comportamental
- [ ] Adicionar interface gráfica
- [ ] Suporte para outros sistemas operacionais
- [ ] Geração de relatórios detalhados

## 📞 Contato

Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para abrir uma issue no GitHub.
