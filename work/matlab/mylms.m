function [ out, errors ] = mylms( in, len, des)

out = zeros([1 length(in)]);
errors = zeros([1 length(in)]);

lmsweights = zeros([1 len]);
mu = 0.0005;
ff = 1;

vals = zeros([1 len]);

for i = 1:length(in)
	vals = circshift(vals,[0 1]);
    vals(1) = in(i);
    %display(vals)
    %display(lmsweights)
    normdenom = 2.2204460492503131e-016;
    for j = 1:len
		out(i) = out(i) + (vals(j) * lmsweights(j));
        normdenom = normdenom + (vals(j)*vals(j));
    end
    %display(normdenom)
    err = des(i) - out(i);
    errors(i) = err;
    %display(mu)
    %display(out(i))
    %display(des(i))
    %display(err)
    %display(ff)
    %display(vals)
    %display(lmsweights)
    for j = 1:len
		lmsweights(j) = ff*lmsweights(j) + mu*(vals(j)/normdenom)*err;
    end
    %display(lmsweights)
end

end
