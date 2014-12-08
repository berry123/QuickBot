clc
clear all
close all

%% Variables:
D = 3.375;
CWxoff = [2.5, -0.5, -2, 3, 0];
CWyoff = [3.5, 4.5, 4, 3.5, 3.5];
CCWxoff = [-2.5, -4.5, -4, -4.5, -4];
CCWyoff = [-1.5, -1.5, -0.5, -2, -2];

%% Calculations:
CWx = mean(CWxoff);
CWy = mean(CWyoff);
CCWx = mean(CCWxoff);
CCWy = mean(CCWyoff);
rCW = sqrt(CWx^2 + CWy^2);
rCCW = sqrt(CCWx^2 + CCWy^2);
EMaxSys = max([rCW,rCCW]);

alpha = mean([(CWx+CCWx)/(-4*D),(CWy-CCWy)/(-4*D)]);
beta = mean([(CWx-CCWx)/(-4*D),(CWy+CCWy)/(-4*D)]);

Ed = (D+B*sin(beta/2))/(D-B*sin(beta/2));
cb = pi/(pi-alpha)
cl = 2/(Ed+1)
cr = Ed*cl

figure
plot(CWxoff,CWyoff,'xk',CCWxoff,CCWyoff,'ok',[-10,10],[0,0],'--k',[-0,0],[-10,10],'--k')
legend('Clockwise Off Positions','Counter-Clockwise Off Positions','location','SouthEast')
xlabel('Off X Position (in)')
ylabel('Off Y Position (in)')
title('Off Positions')
axis([-5,4,-3,5])
