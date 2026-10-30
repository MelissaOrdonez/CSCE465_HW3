Log entry 1:

Used AI to help me understand how all four tasks connect together. I wanted to understand the overall security idea of the assignment and how the vulnerability, exploitation, fixing, and containment parts relate to each other.



Log entry 2:



Used AI to clarify the difference between a vulnerability, exploit, mitigation, and containment. I was getting some of the terms mixed up and wanted to understand what each one specifically meant in the context of the assignment.



Log entry 3:

Used AI to better understand why a buffer overflow can overwrite a return address. I was confused on whether the return address being above the buffer was something only set up for the assignment or if that is actually how stack buffer overflows can work in real programs.



Log entry 4:

Used AI to understand why stack protector and PIE were disabled for the vulnerable version. I wanted to make sure those settings were not what actually created the buffer overflow and understand how they only make exploiting the existing bug easier.



Log entry 5:



Used AI to check the boundary condition for the 128-byte buffer. I wanted to understand whether the program should reject n >= 128 or only n > 128 and how the exact buffer size affects the check.



Log entry 6:



Used AI to understand why adding the bounds check is considered the actual fix while protections like stack canaries, PIE, NX, RELRO, and FORTIFY are considered hardening. This helped me separate fixing the source of the bug from just making it harder to exploit.



Log entry 7:

Used AI to understand what the checksec output actually tells me when comparing the vulnerable and fixed binaries. I wanted to know what each of the protections showed about how the binaries were compiled and why that alone does not prove the buffer overflow was fixed.



Log entry 8:



Used AI to understand why running the parser as a low privilege user was not enough by itself. I was confused on what AppArmor added on top of normal Linux permissions, and the explanation helped me understand the difference between restricting the user and restricting the specific program.



Log entry 9:

Used AI to clarify what successful containment would look like if the vulnerable parser was still exploited. I wanted to understand how AppArmor could block the program from accessing the protected file even though the exploit itself still successfully changed the program's control flow.

