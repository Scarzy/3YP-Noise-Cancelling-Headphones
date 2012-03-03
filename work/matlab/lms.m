function [ out ] = lms( in, mu, len, des)

out = zeros([1 len]);

weights = zeros([1 len]);
mu = 0.8*ones([1 len]);

vals = zeros([1 len]);

for i = 1:length(in)
	vals = circshift(vals,1);
	vals(1) = in(i);
	for j = 1:len
		out(i) = out(i) + (vals(j) * weights(j));
	end
	err = des(i) + out(i);
	for j = 1:len
		weights(j) = weights(j) - mu(j)*in(i)*err;
	end
end

end
