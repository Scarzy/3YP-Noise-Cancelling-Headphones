function [ out ] = my_lms( in, len, des)

out = zeros([1 length(in)]);

weights = zeros([1 len]);
mu = 0.0005*ones([1 len]);
ff = 0.8*ones([1 len]);

vals = zeros([1 len]);

for i = 1:length(in)
	vals = circshift(vals,1);
	vals(1) = in(i);
	for j = 1:len
		out(i) = out(i) + (vals(j) * weights(j));
	end
	err = des(i) - out(i);
	for j = 1:len
		weights(j) = ff(j)*weights(j) + mu(j)*vals(j)*err;
	end
end

end
