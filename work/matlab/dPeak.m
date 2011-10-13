function [ a, pos ] = dPeak( mat )
%dPeak detects a peak in a matrix

a = 0;                      %initialise to 0
pos = 0;
average = 0;
for i = 1:length(mat)       %scroll through array
    average = average + abs(mat(i));    %increase average
    if abs(mat(i)) > a      %if greater, then count it
        a = mat(i);         %store magnitude
        pos = i;            %store location
    end
end

%divide down average
average = average / length(mat);

if abs(a) < 0.5             %Greater than 50% match required, otherwise cancel 
   a = 0;
   pos = 0;
end

end

