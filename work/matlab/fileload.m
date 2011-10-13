function [ out ] = fileload( file )
%FILELOAD Summary of this function goes here
%   Detailed explanation goes here
fil = fopen(strcat('H:\Music\', file),'r');
out = fread(fil, 'int16');

end

