%lab1.m
% Purpose - This is an implimentaion of the UMBark Method for our robot. This plots the results
% and associated data as well
% 
% Alexandre van der Ven de Freitas
% Peter Richard Olejnik
% December 4, 2014

clc
clear all
close all

%% Variables:
D = 30; %in inches
B = 8.5; %in inches
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

%% Plots:

figure
hold on

% Code to plot the points
plot(CWxoff,CWyoff,'xk',CCWxoff,CCWyoff,'ok',[-10,10],[0,0],'--k',[-0,0],[-10,10],'--k')
legend('Clockwise Off Positions','Counter-Clockwise Off Positions','location','SouthEast')
xlabel('Off X Position (in)')
ylabel('Off Y Position (in)')
title('Off Positions')
axis([-8,5,-6,8])

% Code to plot the radii and the centers of gravity
xcw = (CWx-rCW):0.01:(CWx+rCW);
ycw = sqrt(rCW^2 - (xcw-CWx).^2);
plot(xcw,CWy+ycw,'-.k',xcw,CWy-ycw,'-.k')
xccw = (CCWx-rCCW):0.01:(CCWx+rCCW);
yccw = sqrt(rCCW^2 - (xccw-CCWx).^2);
plot(xccw,CCWy+yccw,'-.k',xccw,CCWy-yccw,'-.k')

plot(CWx,CWy,'+k',CCWx,CCWy,'+k')
