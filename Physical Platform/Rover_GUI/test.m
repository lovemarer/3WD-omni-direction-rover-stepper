u = udp('129.127.225.186',2390)
% u = udp('129.127.225.142',2390)
fopen(u)
% Command Format: "x (in cm), y (in cm), speed (in cm/s), acceleration (in cm/s^5), spin(in degree)" 
% Servo order: wrist, shoulder, elbow
% wrist:25 shoulder:170 elbow:50

%%%TRIANGLE
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"50,30,30,15,0,35,170,180")
pause


fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"-50,30,30,15,0,35,170,180")
pause


fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"0,-60,30,15,0,35,170,180")
pause

fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause

fwrite(u,"0,0,30,15,400,35,170,180") %Spin
pause
fwrite(u,"0,0,30,15,-400,35,170,180") %Spin
pause

%%%Secod ride
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"50,30,30,15,0,35,170,180")
pause

fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"0,0,30,15,400,35,170,180") %Spin
pause
fwrite(u,"0,0,30,15,-400,35,170,180") %Spin
pause

fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"-50,30,30,15,0,35,170,180")
pause

fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause

fwrite(u,"0,0,30,15,400,35,170,180") %Spin
pause
fwrite(u,"0,0,30,15,-400,35,170,180") %Spin
pause

fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause

%%%Speed test
fwrite(u,"0,-20,30,15,0,35,170,180")
pause
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"150,0,50,15,0,35,170,180")
pause
fwrite(u,"-150,0,50,15,0,35,170,180")
pause
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause


fwrite(u,"0,-20,30,15,0,35,170,180")
pause
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause
fwrite(u,"150,0,70,25,0,35,170,180")
pause
fwrite(u,"-150,0,70,25,0,35,170,180")
pause
fwrite(u,"0,0,15,15,0,35,170,50") %dp
pause
fwrite(u,"0,0,15,15,0,35,170,180") %rp
pause

fwrite(u,"0,-70,15,15,0,35,170,180")
pause



% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"0,150,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,400,35,170,180")
% pause
% fwrite(u,"0,0,15,15,-400,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"25,-50,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"-25,-100,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"25,100,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
% fwrite(u,"-25,50,15,15,0,35,170,180")
% pause
% fwrite(u,"0,0,15,15,0,35,170,50")
% pause
% fwrite(u,"0,0,15,15,0,35,170,180")
% pause
