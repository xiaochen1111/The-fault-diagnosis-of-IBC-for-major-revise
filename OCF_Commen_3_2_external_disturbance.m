% =========================================================================
% =                                                                       =
% =                   Demo of fault diagnosis                             =
% =                             by                                        =
% =                          Chuanfeng Li                                 =
% =                       date: 01.03.2021                                =
% =                                                                       =
% =                               HIT                                     =
% =                   e-mail: licf1996@gmail.com                          =
% =========================================================================

%     The program is applied for the simulation "OCF_Commen_2_5_PI"
%% Data Acquisition
% Load the Data
clc
N   = 200001:1:1200000;
t   = out.Phase_current{1}.Values.Time(N);
iL1 = out.Phase_current{1}.Values.Data(N);
iL2 = out.Phase_current{2}.Values.Data(N);
iL3 = out.Phase_current{3}.Values.Data(N);
% Gate1_signal=out.Gate_signal{1}.Values.Data(N);
% The sampling value of input current at three specific moments
I_in      = out.Sampling{1}.Values.Data(N);
I_sample1 = out.Sampling{2}.Values.Data(N);
I_sample2 = out.Sampling{3}.Values.Data(N);
I_sample3 = out.Sampling{4}.Values.Data(N);

% D and Outvoltage
Duty_Cycle = out.ScopeData2{3}.Values.Data(N)./1000;
Vout       = out.ScopeData2{2}.Values.Data(N);
Vref        = out.ScopeData2{1}.Values.Data(N);
%% Data Preprocess
clc
N  = length(I_in);
fk = 10e3;
fs = 1./2.5e-8;
NF = fs/fk;
k  = round(NF/3);
Is1_Int = [];
Is2_Int = [];
Is3_Int = [];
dx=0.01;
for i = NF+1:NF:N-3*NF
    is1_Int = trapz(t(i:1:i+2*NF),I_sample1(i:1:i+2*NF));
    is2_Int = trapz(t(i:1:i+2*NF),I_sample2(i:1:i+2*NF));
    is3_Int = trapz(t(i:1:i+2*NF),I_sample3(i:1:i+2*NF));
%     is1_Int = Sum_simple(dx,I_sample1(i:1:i+3*NF));
%     is2_Int = Sum_simple(dx,I_sample2(i:1:i+3*NF));
%     is3_Int = Sum_simple(dx,I_sample3(i:1:i+3*NF));
%     [Ans]=AC_simple(f);
    Is1_Int = [Is1_Int,is1_Int];
    Is2_Int = [Is2_Int,is2_Int];
    Is3_Int = [Is3_Int,is3_Int];
end
%% Visualization
figure(1)
plot(Is1_Int);
hold on
plot(Is2_Int);
hold on
plot(Is3_Int);
%%  Threshould Calculation
clc
Vin = 12;
TT  = 1/fk;
Th = 12/3/L1*TT^2;
%% Fault Diagnosis

II1=[];
II2=[];
II3=[];
NN = length(Is1_Int);
Max_difference = [];
for ii=1:1:NN
    max_difference = max([abs(round(((Is1_Int(ii)-Is2_Int(ii))),12)),abs(round(((Is2_Int(ii)-Is3_Int(ii))),12)),...
        abs(round(((Is1_Int(ii)-Is3_Int(ii))),12))]);
if max_difference< (4e-05)                     %1.8000e-016e-05   
    IIs1_Int=1;
    IIs2_Int=2;
    IIs3_Int=3;
elseif round((Is1_Int(ii)-Is2_Int(ii)).* (Is2_Int(ii)-Is3_Int(ii)),9)>0
    IIs1_Int=1;
    IIs2_Int=2+0.5;
    IIs3_Int=3;
elseif round((Is2_Int(ii)-Is3_Int(ii)).* (Is3_Int(ii)-Is1_Int(ii)),9)>0
    IIs1_Int=1;
    IIs2_Int=2;
    IIs3_Int=3+0.5;
elseif round((Is3_Int(ii)-Is1_Int(ii)).* (Is1_Int(ii)-Is2_Int(ii)),9)>0
    IIs1_Int=1+0.5;
    IIs2_Int=2;
    IIs3_Int=3;
else
    IIs2_Int=2;
    IIs3_Int=3;
    IIs1_Int=1;
end
II1=[II1,IIs1_Int];
II2=[II2,IIs2_Int];
II3=[II3,IIs3_Int];
Max_difference = [Max_difference,max_difference ];
end
Y = linspace(Th,Th,length(Max_difference));
T = linspace(t(1),t(end),length(Max_difference));
pict = Plot(T,Max_difference,T,Y);
%% Picture Direct Result
color = '';
T = linspace(t(1),t(end),length(II3));
figure(2)
subplot(211)
PPP = 0;
plt=plot(t,I_sample1);Picture_LCF;
subplot(212)
PPP = 1;
plt=plot(T,II1);
Picture_LCF;
hold on
plt=plot(T,II2);
Picture_LCF;
hold on
plt=plot(T,II3);
Picture_LCF;
%% Picture Output Voltage、Reference valltage、Integral and Threshold
subplot(311)
plt = plot(t,I_in);
color = 'r';
Picture_LCF;
ylabel("(a) Output voltage(V)",'FontSize',14.5)
subplot(312)
plt = plot(T,Max_difference);
color = 'p';
Picture_LCF;
hold on
plt = plot(T,Y);
color = 'lb';
Picture_LCF;
ylabel("(b) Threshold",'FontSize',14.5)
subplot(313)
color = '';
PPP = 1;
plt=plot(T,II1);
Picture_LCF;
hold on
plt=plot(T,II2);
Picture_LCF;
hold on
plt=plot(T,II3);
set(gca,'Ylim',[0.8,3.7])
Picture_LCF;
ylabel("(c) Indicator",'FontSize',14.5)
legend("CI_{P1}","CI_{P2}","CI_{P2}")
set(gcf,'position',[0 0 600 500])
%% Picture Output Voltage、Reference valltage、Integral and Threshold
subplot(311)
plt = plot(t,Vref);
color = 'o';
Picture_LCF;
hold on
plt = plot(t,Vout);
color = 'g';
Picture_LCF;
ylabel("(a) Output voltage(V)",'FontSize',14.5)
legend("Reference voltage","Output voltage")
subplot(312)
plt = plot(T,Max_difference);
color = 'p';
Picture_LCF;
hold on
plt = plot(T,Y);
color = 'lb';
Picture_LCF;
ylabel("(b) Threshold",'FontSize',14.5)
subplot(313)
color = '';
PPP = 1;
plt=plot(T,II1);
Picture_LCF;
hold on
plt=plot(T,II2);
Picture_LCF;
hold on
plt=plot(T,II3);
set(gca,'Ylim',[0.8,3.7])
Picture_LCF;
ylabel("(c) Indicator",'FontSize',14.5)
legend("CI_{P1}","CI_{P2}","CI_{P2}")
set(gcf,'position',[0 0 600 500])
%% Picture fig 4
T = linspace(t(1),t(end),length(II3));
figure(3)
subplot(311)
color = 'r';
plt=plot(t,I_in);
Picture_LCF;
ylabel("(a) Input current",'FontSize',14.5)
subplot(312)
plt = plot(T,Max_difference);
Picture_LCF;
hold on
plt = plot(T,Y);
Picture_LCF;
ylabel("(c) Threshold",'FontSize',14.5)
subplot(313)
color = '';
PPP = 1;
plt=plot(T,II1);
Picture_LCF;
hold on
plt=plot(T,II2);
Picture_LCF;
hold on
plt=plot(T,II3);
set(gca,'Ylim',[0.8,3.7])
Picture_LCF;
ylabel("(c) Indicator",'FontSize',14.5)
legend("CI_{P1}","CI_{P2}","CI_{P2}")
set(gcf,'position',[0 0 600 500])
%% Picture 2 
% input Volatge output Voltage Duty cycle 
figure(2)
PPP = 0;
subplot(311)
plt = plot(t,I_in);
ylabel("(a) Input current",'FontSize',14.5)
color = 'lb';
Picture_LCF;
subplot(312)
plt = plot(t,Vout);
ylabel("(b) Output voltage",'FontSize',14.5)
color = 'g';
Picture_LCF;
subplot(313)
plt = plot(t,Duty_Cycle);
color = 'o';
Picture_LCF;
ylabel("(c) Duty cycle",'FontSize',14.5)
%% Test
K=[];
for i=1:1:95;
KK=max([abs(round(((Is1_Int(i)-Is2_Int(i))),11)),abs(round(((Is2_Int(i)-Is3_Int(i))),11)),...
        abs(round(((Is1_Int(i)-Is3_Int(i))),11))]);
    K=[K,KK];
end
plot(K)

%% Simple Sum
function [Ans]=Sum_simple(dx,f)
Ans=0;
N=length(f);
for t=1:1:N
    an=f(t).*dx;
    Ans=Ans+an;
end
end
%% Simple Autocorrelation
function [Ans]=AC_simple(f);
Ans=0;
N=length(f);
[Ans,b]=xcorr(f,'unbiased');
end