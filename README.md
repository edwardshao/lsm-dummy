A Dummy LSM for Testing
========
A dummy LSM for testing and only hook mkdir call.<br>
I write the LSM as a kernel module and export "security_hook_heads" variable is required.<br>
Check [the patch](0001-export-security_hook_heads-variable.patch) for exporting "security_hook_heads" variable.
