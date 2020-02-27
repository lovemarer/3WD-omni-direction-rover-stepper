u = udp('129.127.225.186',2390)
% u = udp('129.127.225.142',2390)
fopen(u)
% Command Format: "x (in cm), y (in cm), speed (in cm/s), acceleration (in cm/s^2), spin(in degree)" 
% Servo order: wrist shoulder elbow
% wrist:25 shoulder:170 elbow:50

fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"0,150,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,400,35,170,180")
pause
fwrite(u,"0,0,30,10,-400,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"25,-50,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"-25,-100,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"25,100,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
fwrite(u,"-25,50,30,10,0,35,170,180")
pause
fwrite(u,"0,0,30,10,0,35,170,50")
pause
fwrite(u,"0,0,30,10,0,35,170,180")
pause
