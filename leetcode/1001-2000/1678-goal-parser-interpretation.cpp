class Solution {
public:
    string interpret(string command) {
        int n = command.size(), m = 0;
        for(int i = 0; i < n; ) {
            if(i + 1 < n && command[i] == '(') {
                if(command[i + 1] == ')') {
                    command[m++] = 'o';
                    i += 2;
                    continue;
                }
                if(i + 3 < n && command.substr(i + 1, 3) == "al)") {
                    command[m++] = 'a';
                    command[m++] = 'l';
                    i += 4;
                    continue;
                }
            }
            command[m++] = command[i++];
        }
        command.resize(m);
        return command;
    }
};
