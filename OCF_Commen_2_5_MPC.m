% =========================================================================
% =                                                                       =
% =                   Demo of fault diagnosis                             =
% =                             by                                        =
% =                          Chuanfeng Li                                 =
% =                       date: 12.17.2020                                =
% =                                                                       =
% =                               HIT                                     =
% =                   e-mail: licf1996@gmail.com                          =
% =========================================================================
% A fault diagnosis for the MPC. 
%     The program is applied for the simulation "IBC_MPC_comment_2_5"
%% Data Acquisition
% Load the Data
clc
N    = 420001:1:1200000;
t    = out.Phase_current{1}.Values.Time(N);
I_in = out.Phase_current{1}.Values.Data(N);
iL1  = out.Phase_current{2}.Values.Data(N);
iL2  = out.Phase_current{3}.Values.Data(N);
iL3  = out.Phase_current{4}.Values.Data(N);
% Gate1_signal=out.Gate_signal{1}.Values.Data(N);
% The sampling value of input current at three specific moments
I_sample1 = out.Sample_value{2}.Values.Data(N);
I_sample2 = out.Sample_value{3}.Values.Data(N);
I_sample3 = out.Sample_value{4}.Values.Data(N);

% D and Outvoltage
Duty_Cycle = out.Duty_cycle{1}.Values.Data(N);
Vout       = out.Output_Gate{5}.Values.Data(N);
%% Data Preprocess
clc
N  = length(I_in);
fk = 10e3;
fs = 1./2.5e-8;
NF = round(fs/fk);
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
TT  = 1/fk;
Th = 12/3/L1*TT^2;
%% Fault Diagnosis

II1=[];
II2=[];
II3=[];
Max_difference = [];
NN = length(Is1_Int);
for ii=1:1:NN
max_difference = max([abs(round(((Is1_Int(ii)-Is2_Int(ii))),12)),abs(round(((Is2_Int(ii)-Is3_Int(ii))),12)),...
        abs(round(((Is1_Int(ii)-Is3_Int(ii))),12))]);
Max_difference = [Max_difference,max_difference]; 
if  max_difference < (4e-05)
    IIs1_Int=1;
    IIs2_Int=2;
    IIs3_Int=3;
elseif round((Is1_Int(ii)-Is2_Int(ii)).* (Is2_Int(ii)-Is3_Int(ii)),10)>0
    IIs1_Int=1;
    IIs2_Int=2+0.5;
    IIs3_Int=3;
elseif round((Is2_Int(ii)-Is3_Int(ii)).* (Is3_Int(ii)-Is1_Int(ii)),10)>0
    IIs1_Int=1;
    IIs2_Int=2;
    IIs3_Int=3+0.5;
elseif round((Is3_Int(ii)-Is1_Int(ii)).* (Is1_Int(ii)-Is2_Int(ii)),10)>0
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
end


Y = linspace(Th,Th,length(Max_difference));
T = linspace(t(1),t(end),length(Max_difference));
pict = Plot(T,Max_difference,T,Y);
%% Picture
T = linspace(t(1),t(end),length(II3));
figure(2)
color = '';
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
%% Picture fig 5
%% Picture 3
% Plot duty cycle the intergral and fault indicator
TTT = linspace(t(1),t(end),length(II3));
subplot(411)
plt = plot(t,Duty_Cycle);
color = 'o';
Picture_LCF;
ylabel("(a) Duty cycle",'FontSize',14.5)
subplot(412)
color = '';
PPP = 1;
plt = plot(T,Is1_Int);
Picture_LCF;
hold on
plt = plot(T,Is2_Int);
Picture_LCF;
hold on
plt = plot(T,Is3_Int);
Picture_LCF;
ylabel("(b) Integral",'FontSize',14.5)
subplot(413)
plt = plot(T,Max_difference);
Picture_LCF;
hold on
plt = plot(T,Y);
Picture_LCF;
ylabel("(c) Threshold",'FontSize',14.5)
subplot(414)
color = '';
PPP = 1;
plt = plot(T,II1);
Picture_LCF;
hold on
plt = plot(T,II2);
Picture_LCF;
hold on
plt = plot(T,II3);
Picture_LCF;
set(gca,'YLim',[0.8,3.7]);
ldf = legend('CI_{P1}','CI_{P2}','CI_{P3}','FontSize',12);
ldf.NumColumns = 3;
ylabel("(d) Fault Indicator",'FontSize',14.5);
set(gcf,'position',[0 0 600 500])
%% Picture fig 4
T = linspace(t(1),t(end),length(II3));
figure(3)
subplot(411)
PPP = 0;
color = '';
plt=plot(t,I_sample1);Picture_LCF;
subplot(412)
plt = plot(t,Vout);Picture_LCF;
subplot(413)
plt = plot(t,Duty_Cycle);Picture_LCF;
subplot(414)
PPP = 1;
plt=plot(T,II1);
Picture_LCF;
hold on
plt=plot(T,II2);
Picture_LCF;
hold on
plt=plot(T,II3);
Picture_LCF;
%% Test
K=[];
for i=1:1:95;
KK=max([abs(round(((Is1_Int(i)-Is2_Int(i))),11)),abs(round(((Is2_Int(i)-Is3_Int(i))),11)),...
        abs(round(((Is1_Int(i)-Is3_Int(i))),11))]);
    K=[K,KK];
end
plot(K)
%% Picture 3
% Plot duty cycle the intergral and fault indicator
figure(3)
subplot(411)
plt = plot(t,Duty_Cycle);
color = 'o';
Picture_LCF;
ylabel("(a) Duty cycle",'FontSize',14.5)
subplot(412)
color = '';
PPP = 1;
plt = plot(T,Is1_Int);
Picture_LCF;
hold on
plt = plot(T,Is2_Int);
Picture_LCF;
hold on
plt = plot(T,Is3_Int);
Picture_LCF;
ylabel("(b) Integral",'FontSize',14.5)
subplot(413)
plt = plot(T,Max_difference);
Picture_LCF;
hold on
plt = plot(T,Y);
Picture_LCF;
ylabel("(c) Threshold",'FontSize',14.5)
subplot(414)
color = '';
PPP = 1;
plt = plot(T,II1);
Picture_LCF;
hold on
plt = plot(T,II2);
Picture_LCF;
hold on
plt = plot(T,II3);
Picture_LCF;
set(gca,'YLim',[0.8,3.7]);
ylabel("(d) Fault Indicator",'FontSize',14.5)
set(gcf,'position',[0 0 600 500])
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
%% Sampling and holding
function [IL_sampling_hold] = sampling_holding(TT_start,I_in,N) 

IL_sampling = I_in(TT_start:N:length(I_in));
IL_sampling_rep = (repmat(IL_sampling,1,N))';
[mm,nn] = size(IL_sampling_rep);
IL_sampling_hold = reshape(IL_sampling_rep,(mm*nn),1);
end