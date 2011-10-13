function [ a, pos ] = dPeak( mat )
%dPeak detects a peak in a matrix

a = 0;                      %initialise to 0
pos = 0;
for i = 1:length(mat)
    if abs(mat(i)) > a
        a = mat(i);
        pos = i;
    end
end

end

