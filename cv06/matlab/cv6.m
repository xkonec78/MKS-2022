close all;
clear all;

raw = csvread("ntc.csv")';
t = raw(1,:);
Rntc = raw(2,:);

Uref = 3.3; 
Nbit = 10;
ad1 = Rntc./(Rntc+10).*2^Nbit;

figure
plot(ad1, t, 'o')
hold on
grid on
p = polyfit(ad1, t, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on, plot(ad2, t2, 'r');

dlmwrite('data.dlm', t2*10, ',');

%% ADC = Uin/Uref * 2^Nbit