#include <iostream>

#include <cstring>
#include <cstdlib>

using namespace std;

int registers[10] = {};
void help(){
     cout << "Supported commands:" << endl
          << "quit" << endl
          << "cmd.prompt" << endl
          << "asm.reg.set" << endl
          << "asm.reg.add" << endl
          << "asm.reg.dbg" << endl
          << "help" << endl;
};
void cmdprompt(char line[],char prompt[]){
     char* argument = line + strlen("cmd.prompt "); 
            if (strlen(argument) < 100 && *argument != '\0')
				strcpy(prompt, argument);
};
int asmregset(char line[]){
     char* arguments = line + strlen("asm.reg.set ");
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                cout << "ERROR" << endl;
                return 1;
            }
            int reg = *arguments - '0';
            arguments += 2;
            char* endOfNumber = NULL;
            long number = strtol(arguments, &endOfNumber, 0);
            if (!endOfNumber || *endOfNumber != '\0' 
                || number < -100 || number > 100) { 
                cout << "ERROR:overflow" << endl;
                return 2;
            }
            registers[reg] = number;
            return 3;
};
int asdregadd(char line[]){
     char* arguments = line + strlen("asm.reg.set ");
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                cout << "ERROR" << endl;
                return 3;
            }
            int reg1 = *arguments - '0';
            arguments += 2;
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                cout << "ERROR" << endl;
                return 3;
            }
            int reg2 = *arguments - '0';
            arguments += 2;
            if (*arguments < '0' || *arguments > '9' || arguments[1] != '\0') {
                cout << "ERROR" << endl;
                return 3;
            }
            int reg3 = *arguments - '0';
            
            int sum = registers[reg2] + registers[reg3];
            if (sum > 100 || sum < -100) {
                cout << "ERROR:overflow" << endl;
                return 2;
            }
            
            registers[reg1] = sum;
            return 1;
};
void asmregdbg(){
     for (int i=0; i < 10; i++) {
                cout << "REG_" << i << " = " << registers[i] << endl;
            }
};
int main()
{
    char line[1000];
    char prompt[100] = ">";
    
    
    while(true) {
        cout << prompt << " ";
        cin.getline(line, 1000);
        if (strcmp(line, "quit") == 0) {
           break;
        } else if (strcmp(line, "help") == 0) {
            help();
        } else if (strncmp(line, "cmd.prompt ", strlen("cmd.prompt ")) == 0) {
            cmdprompt(line,prompt);
        } else if (strncmp(line, "asm.reg.set ", strlen("asm.reg.set ")) == 0) {
           if(asmregset(line)==1)
                continue; 
             else  if(asmregset(line)==2)
                continue;
                else if(asmregset(line)==3)cout << "OK" << endl;
        } else if (strncmp(line, "asm.reg.add ", strlen("asm.reg.add ")) == 0) {
           if(asdregadd(line)==3) continue;
           else if (asdregadd(line)==2)continue;
           else if (asdregadd(line)==1)cout << "OK" << endl;
        } else if (strncmp(line, "asm.reg.dbg", strlen("asm.reg.dbg")) == 0) {
            asmregdbg();
        } else {
            cout << "Unknown command " << line << endl; 
        }
    }
    return 0;
}