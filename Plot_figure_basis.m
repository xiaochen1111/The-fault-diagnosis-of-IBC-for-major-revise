% plot for A samplingvalues and integral
% laod the data
% The inductor current and the input current
% Load the Data
clc
N   = 320001:1:720000;
t   = out.Phase_current{1}.Values.Time(N);
iL1 = out.Phase_current{1}.Values.Data(N);
iL2 = out.Phase_current{2}.Values.Data(N);
iL3 = out.Phase_current{3}.Values.Data(N);
Tr2 = out.Phase_current{4}.Values.Data(N);
%Gate1_signal=out.Gate_signal{1}.Values.Data(N);
% The sampling value of input current at three specific moments
I_in      = out.Sample_value{1}.Values.Data(N);
I_sample1 = out.Sample_value{2}.Values.Data(N);
I_sample2 = out.Sample_value{3}.Values.Data(N);
I_sample3 = out.Sample_value{4}.Values.Data(N);
%% Plot 
T=linspace(0.018,0.028,96);
NN=1:1:96;
I1_In=Is1_Int(NN);
I2_In=Is2_Int(NN);
I3_In=Is3_Int(NN);
NNN= 145:1:160;
%% 
% figure(1)
% ha = tight_subplot(3,1,[.13 .003],[.13 .08],[.102 .04]); %调整图窗大小(gap down up left right)
% set(gca,'XLim',[0.0095,0.012])
figure(1)
% ha = tight_subplot(2,1,[.15 .03],[.15 .1],[.11 .04]); %调整图窗大小(gap down
% up left right) %650 400
ha = tight_subplot(2,1,[.15 .10],[.15 ,0.1],[.09 .04]);
 %%  Inductor Current
PPP = 1;
plt = plot(t,iL1);
Picture_LCF;
hold on
plt = plot(t,iL2);
Picture_LCF;
hold on
plt = plot(t,iL3);
Picture_LCF;    
legend('I_{L1}','I_{L2}','I_{L3}')
ylabel('Inductor Current(A)','FontSize',15,'LineWidth',12)  
Picture_LCF;
%% Fault Indicator
color = '';
PPP = 1;
plt = plot(T,y1);
Picture_LCF;
hold on
plt = plot(T,y2);
Picture_LCF;
hold on
plt = plot(T,y3);
ylabel('Indicator','FontSize',15,'LineWidth',12) 
legend('CI_{P1}','CI_{P2}','CI_{P3}');
Picture_LCF;
set(gca,'YLim',[0.8,3.7])
%% Gate Signal
PPP=4;
plt = plot(t,Gate1_signal);
ylabel('G1','FontSize',15,'LineWidth',12) 
Picture_LCF;
%% Sampling Data
PPP = 1;
plt = plot(T,Is1_Int);
Picture_LCF;
hold on
plt = plot(T,Is2_Int);
Picture_LCF;
hold on
plt = plot(T,Is3_Int);
legend('$\hat{I}_{in}(T1)$','$\hat{I}_{in}(T2)$','$\hat{I}_{in}(T3)$', 'Interpreter', 'latex');
ylabel('I_{Integral}(A)','FontSize',15,'LineWidth',12) 
Picture_LCF;
set(gca,'YLim',[2e-3,5e-3])
set(gca,'XLim',[0.0095,0.012])



%% Inductor Current\
%  figure(3)
%a = tight_subplot(1,1,[.17 .003],[.17 .08],[.09 .04]); %调整图窗大小(gap down up left right)
PPP = 1;
plt = plot(t,iL1);
Picture_LCF;
hold on
plt = plot(t,iL2);
Picture_LCF;
hold on
plt = plot(t,iL3);
Picture_LCF;    
legend('I_{L1}','I_{L2}','I_{L3}')
ylabel('Inductor Current(A)','FontSize',15,'LineWidth',12)  
Picture_LCF;

%% subpicture
axes('position', [0.18 0.18, 0.35, 0.22])
%% 
h=figure(1);
%codes to generate figure;
% set(h,'PaperPositionMode','manual');
% set(h,'PaperUnits','points');
%set(h,'PaperPosition',[0,0,650,400]);%恰当选择尺寸
%print(h,'C:\Users\Dell\Desktop\Fig10.tiff','-painters','-r600','-dtiffn');%-r600可改�?300dpi分辨�?
saveas(h,'C:\Users\Dell\Desktop\Fig12.mfig')
%exportgraphics(gcf,'C:\Users\Dell\Desktop\test.tiff','Resolution',600);
%exportgraphics(gcf,'C:\Users\Dell\Desktop\test.tiff','Resolution',600);