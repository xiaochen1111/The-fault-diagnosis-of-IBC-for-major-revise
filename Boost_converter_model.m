%% 打开仿真文件
mdl = 'IBC_open_basis_test_frequency_analysis';
open_system(mdl);
%% 指定输入输出量
ios = [...
    linio([mdl,'/Constant1'],1,'input'); ...
    linio([mdl,'/Voltage Measurement'],1,'output')];
f = logspace(log10(200),log10(80000),20);
in = frest.Sinestream('Frequency',f,'Amplitude',0.05,...
    'FreqUnits','Hz');
getSimulationTime(in)/0.02
%% 画图+拟合
[sysData,simlog] = frestimate(mdl,ios,in);
bopt               = bodeoptions;
bopt.Grid          = 'on';
bopt.PhaseMatching = 'on';
figure, bode(sysData,'*r',bopt)
hold on
s = tf('s')
Vg=12; C=370e-6; L=333.33e-6; R=2; Vo=24; D = 0.5;
GIden = (-Vg/R/(1-D)^2 * L * s + Vg)/...
  (L * C * s^2 + L/R * s + (1-D)^2)

bode(GIden,{200,1e6*6.28})
sysA = tfest(sysData,2)
figure, bode(sysData,'r*',sysA,bopt)