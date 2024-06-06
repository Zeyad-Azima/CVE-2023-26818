# Disclaimer
This exploit has been created solely for the purposes of research and for the development of effective defensive techniques. It is not intended to be used for any malicious or unauthorized activities. The author and the owner of the script disclaim any responsibility or liability for any misuse or damage caused by this software. Users are urged to use this software responsibly and only in accordance with applicable laws and regulations. Not for non-ethical usages.

# CVE-2023-26818
CVE-2023-26818 Exploit MacOS TCC Bypass W/ Telegram. You can read the vulnerability analysis <a href="https://zeyadazima.com/macos/CVE_2023_26818_P1/">Part 1</a> and <a href="https://zeyadazima.com/macos/CVE_2023_26818_P2/">Part 2</a> for sandbox bypass.

![Screenshot 2023-09-11 at 8 43 14 PM](https://github.com/Zeyad-Azima/CVE-2023-26818/assets/62406753/c207212b-050e-4ae7-a1ac-5e26abbeb391)


# Video

[![CVE-2023-26818](https://img.youtube.com/vi/fV9f7ZG5vFE/0.jpg)](https://www.youtube.com/watch?v=fV9f7ZG5vFE)


# Manual Compile and Usage
## Camera
```
gcc -dynamiclib -framework Foundation -framework AVFoundation Camexploit.m -o Cam.dylib
```
![image](https://github.com/Zeyad-Azima/CVE-2023-26818/assets/62406753/220f774e-6532-417b-b5e2-177b13752397)

## Microphone
```
gcc -dynamiclib -framework Foundation -framework AVFoundation Micexploit.m -o Micexploit.dylib
```
![image](https://github.com/Zeyad-Azima/CVE-2023-26818/assets/62406753/3b27cf97-4205-4732-8eb5-cc526bc6a1c8)

## Location
```
gcc -dynamiclib -framework Foundation -framework CoreLocation -framework AVFoundation Locexploit.m -o Locexploit.dylib
```
![image](https://github.com/Zeyad-Azima/CVE-2023-26818/assets/62406753/2283da05-4899-46d8-a93a-7d34bca23a3c)
