Homework 3: From Prompt to Process





This assignment is about software security, stack buffer overflows, program hardening, and access control using Linux permissions and AppArmor.



This README has the setup, files, and main commands I used.







Setup of VM and Required Tools





VM and Course Folder



\- Start Oracle VirtualBox - VM: ubuntu\_24.04\_VB\_LinuxVMImages.COM



\- Go to the HW3 folder:



cd \~/csce465-agentsec/hw3/CSCE465\_HW3





\- Install the required tools:



sudo apt update

sudo apt install -y build-essential gdb binutils checksec apparmor-utils





\- Verify the tools:



gcc --version

gdb --version

checksec --version

aa-status --version







Assignment Files





\- The HW3 folder contains:



report.pdf



README.md



AI\_USAGE\_KARLA\_S.md



AI\_LOGS\_KARLA\_S.md



AI\_USAGE\_MELISSA\_O.md



AI\_LOGS\_MELISSA\_O.md



payload.bin



src/



policy/



skills/



web/



tests/



inbox/



markers/





\- The src/ folder contains:



legacy\_log\_parser.c



legacy\_log\_parser\_fixed.c



make\_payload.py





\- The policy/ folder contains:



apparmor.profile





\- The skills/legacy-parser/ folder contains:



SKILL.md



run\_parser.sh





\- The web/ folder contains:



adversarial.html







Assignment Tasks





Task 1 - Vulnerable Parser and Buffer Overflow



\- Go to the source folder:



cd \~/csce465-agentsec/hw3/CSCE465\_HW3/src





\- Compile the vulnerable parser:



gcc -O0 -g -fno-stack-protector -no-pie -Wl,-z,noexecstack 

\-Wall -Wextra -o legacy\_log\_parser legacy\_log\_parser.c





\- Check the binary security properties:



checksec --file=./legacy\_log\_parser





\- GDB is used to find the exact overflow offset and the address of win().



\- make\_payload.py is used to create the exploit payload.



\- The payload redirects execution to win() and demonstrates the stack buffer overflow.







Task 2 - Agent-Mediated Invocation



\- The local OpenClaw skill is stored in:



skills/legacy-parser/





\- The skill contains:



SKILL.md



run\_parser.sh





\- The adversarial webpage is stored in:



web/adversarial.html





\- The inbox/ directory is used for files that the agent is allowed to pass to the parser.



\- The adversarial webpage contains untrusted content intended to influence the agent into invoking the vulnerable parser.



\- The execution trace shows the path from untrusted webpage content, to a tool decision, and then to the vulnerable native program.







Task 3 - Fixed and Hardened Parser



\- Go to the source folder:



cd \~/csce465-agentsec/hw3/CSCE465\_HW3/src





\- Compile the fixed parser:



gcc -O2 -g -fstack-protector-strong -D\_FORTIFY\_SOURCE=3 

\-fPIE -pie -Wl,-z,relro,-z,now -Wl,-z,noexecstack 

\-Wall -Wextra -Werror 

\-o legacy\_log\_parser\_fixed legacy\_log\_parser\_fixed.c





\- Compare the vulnerable and fixed binaries:



checksec --file=./legacy\_log\_parser



checksec --file=./legacy\_log\_parser\_fixed





\- The fixed version adds a bounds check so oversized input is rejected before it is copied into the 128-byte buffer.



\- The hardened version also enables protections including stack canaries, PIE, Full RELRO, NX, and FORTIFY.





\- The tests cover:



valid short input



exactly 128 bytes



129 bytes



missing file



original exploit payload





\- The fixed parser accepts valid input and rejects oversized input, including the original exploit payload.







Task 4 - Access Control and AppArmor



\- The AppArmor profile is stored in:



policy/apparmor.profile





\- Check the profile syntax:



sudo apparmor\_parser -Q policy/apparmor.profile





\- Load or reload the profile:



sudo apparmor\_parser -r policy/apparmor.profile





\- Verify that the profile is loaded:



sudo aa-status | grep legacy\_log\_parser





\- The vulnerable parser is run as the low-privilege agentlab user.



\- The AppArmor profile allows the parser to read the selected payload, limits writes to the markers/ directory, denies access to /opt/agentsec/decoy.txt, prevents shell execution, and allows the files and libraries required for the parser to run.



\- The markers/ directory stores the marker created when win() is reached.



\- The denial logs show that AppArmor blocks access to the protected decoy file even when the vulnerable parser is successfully exploited.







AI Usage





\- AI usage for both members is documented in:



AI\_USAGE\_KARLA\_S.md



AI\_LOGS\_KARLA\_S.md



AI\_USAGE\_MELISSA\_O.md



AI\_LOGS\_MELISSA\_O.md

