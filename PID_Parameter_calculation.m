% =========================================================================
% =                                                                       =
% =            PID Controller Parameter Calculation                       =
% =                             by                                        =
% =                          Chuanfeng Li                                 =
% =                       date: 02.03.2020                                =
% =                                                                       =
% =                               HIT                                     =
% =                   e-mail: licf1996@gmail.com                          =
%  PID Controller Parameter Calculation
%% Calculate the KI and KP
clc
clear all
format long
syms Kip Kii w s Kvp Kvi
Vg = 12; C  = 370e-6; L  = 1000e-6; R  = 2; Vo = 24;
fc = 1e3;
w  = 2*pi*fc;
D  = Vg/Vo;
Dp = 1-Vg/Vo;
PM = 75;
Vm = 1000;
s  = w*1j;

GiPI = (Kip*s+Kii)/(s);
Gid  = 3*(Vo*C*s+2*Vo/R)/(Vm*(L*C*s^2+(L/R)*s+3*(1-D)^2));
a1   = Gid;
a    = sqrt((Kip*w)^2+(Kii)^2)/w;
b    = atan(Kip*w/Kii)-pi/2;

ab   = abs(a1);
an   = angle(a1);

exp1 = [ab*a == 1,b+an == -(180-PM)/(180/pi)];
solu = vpasolve(exp1,[Kip,Kii]);
[solu.Kip,solu.Kii]
%% 波特图绘制
num1=[double(solu.Kip) double(solu.Kii)];
den1=[1 0];%电流环pi
num=[3*Vo*C 3*2*Vo/R];
den=[Vm*L*C Vm*(L/R) 3*Vm*(1-D)^2];

PI=tf(num1,den1);
G=tf(num,den);
Gopen=G*PI;


figure('Name','1 - 开环传函波特图','NumberTitle','off');
bode(G,{100,1e6});

figure('Name','2 - PI控制器波特图','NumberTitle','off');
bode(PI,{100,1e6});

figure('Name','3 - 补偿后系统波特图','NumberTitle','off');
bode(G,'r--',Gopen,{100,1e6});
h = findobj(gcf,'Type','line');
set(h, 'LineWidth', 2);
% .LineStyle
% = ':'
legend('G','Gopen')
grid
%% Voltage loop PI parameter calculation
clc
clear all
format long
syms Vm w s Kip Kii Kvp Kvi w Vg C L R w T K s Vo D Dp
Vg = 12; C  = 370e-6; L  = 1000e-6; R  = 2; Vo = 24;
fc = 0.08e3;
w  = 2*pi*fc;
D  = Vg/Vo;
Dp = 1-Vg/Vo;
PM = 75;
Vm = 1000;
s  = w*1j;
Kip  = 77.738292364102001535116841188175; 
Kii  = 38432.721244442002763594847678325;
GiPI = (Kip*s+Kii)/(s);
Gid  = 3*(Vo*C*s+2*Vo/R)/(Vm*(L*C*s^2+(L/R)*s+3*Dp^2));  

GvPI = (Kvp*s+Kvi)/(s) ;
Gvi  = (3*Dp^2*R-L*s)/(3*Dp*R*C*s+3*2*Dp);

a1   = (Gvi*Gid*GiPI)/(1+Gid*GiPI);

% collect(a1,s)
%%
ab   = abs(a1);
an   = angle(a1);
a    = sqrt((Kvp*w)^2+(Kvi)^2)/w;
b    = atan(Kvp*w/Kvi)-pi/2;
exp1 = [ab*a==1,b+an==-(180-PM)/(180/pi)];
solu = vpasolve(exp1,[Kvp,Kvi]);
[solu.Kvp,solu.Kvi]
%% 波特图绘制程序
num1  = [double(solu.Kvp) double(solu.Kvi)];
den1  = [1 0];
num=[(-Kip*L*Vo) (3*Kip*R*Vo*Dp^2 - Kii*L*Vo)     3*Dp^2*Kii*R*Vo];
den=[C*Dp*L*R*Vm ,...
        (Dp*L*Vm + 3*C*Dp*Kip*R*Vo) , ... 
             (3*2*Dp*Kip*Vo + 3*Dp^3*R*Vm + 3*C*Dp*Kii*R*Vo) ,...
                  3*2*Dp*Kii*Vo ];
PI    = tf(num1,den1);
G     = tf(num,den);
Gopen = G*PI;
% Gopen=Gopen/(1+Gopen) %%电压环闭环传函
figure('Name','1 - G3电压环控制对象波特图','NumberTitle','off');
bode(G,{100,1e6});

figure('Name','2 - 电压环PI控制器波特图','NumberTitle','off');
bode(PI,{100,1e6});

figure('Name','3 - 电压环补偿后波特图','NumberTitle','off');
bode(G,'r--',Gopen,{100,1e6});
h = findobj(gcf,'Type','line');
set(h, 'LineWidth', 2);
legend('G','Gopen')
grid