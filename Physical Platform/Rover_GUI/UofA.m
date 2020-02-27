u = udp('129.127.225.186',2390)
% u = udp('129.127.225.142',2390)
fopen(u)
% Command Format: "x (in cm), y (in cm), speed (in cm/s), acceleration (in cm/s^2), spin(in degree)" 
%U
fwrite(u,"0,-25,10,5,0,35,170,50")
pause
fwrite(u,"18,0,10,5,0,35,170,50")
pause
fwrite(u,"0,25,10,5,0,35,170,50")
pause
fwrite(u,"0,-25,10,5,0,35,170,180")
pause

%move
fwrite(u,"13,0,10,5,0,35,170,180")
pause

%o
fwrite(u,"12,0,10,5,0,35,170,50")
pause
fwrite(u,"0,16,10,5,0,35,170,50")
pause
fwrite(u,"-12,0,10,5,0,35,170,50")
pause
fwrite(u,"0,-16,10,5,0,35,170,50")
pause

%move
fwrite(u,"28,0,10,5,0,35,170,180")
pause

%F
fwrite(u,"0,28,10,5,0,35,170,50")
pause
fwrite(u,"12,0,10,5,0,35,170,50")
pause
fwrite(u,"-12,-12,10,5,0,35,170,180")
pause
fwrite(u,"12,0,10,5,0,35,170,50")
pause
fwrite(u,"-12,0,10,5,0,35,170,180")
pause
fwrite(u,"0,-16,10,5,0,35,170,180")
pause


%move
fwrite(u,"23,0,10,5,0,35,170,180")
pause

%A
fwrite(u,"15,28,10,5,0,35,170,50")
pause
fwrite(u,"8,-14,10,5,0,35,170,50")
pause
fwrite(u,"-15,0,10,5,0,35,170,50")
pause
fwrite(u,"15,0,10,5,0,35,170,180")
pause
fwrite(u,"8,-14,10,5,0,35,170,50")
pause
fwrite(u,"30,0,10,5,0,35,170,180")
pause
