function [ ] = filewrite( file, data )
%FILELOAD Summary of this function goes here
%   Detailed explanation goes here
fil = fopen(strcat('H:\Music\', file),'w');
fwrite(fil, data, 'int16');
fclose(fil);

end

