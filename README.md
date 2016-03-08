A Dummy LSM for Testing
========
A dummy LSM for testing and only hook mkdir call.
I write the LSM as a kernel module and export "security_hook_heads" variable is requested.
Check the patch for exporting "security_hook_heads" variable.
