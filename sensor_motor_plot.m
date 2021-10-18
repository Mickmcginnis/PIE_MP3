clc
clf
clear all

vals = importdata('cleaned_4_matlab.txt');

Sleft = vals.data(:,1);
Mleft = vals.data(:,2);
Sright = vals.data(:,3);
Mright = vals.data(:,4);


t = 0:20:(20*length(data));  %time steps are 20ms

figure(1)
%plot(t, 