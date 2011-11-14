function [ out ] = multiPath( signal , tchain , delay )
%multiPath Applies a multi path effect to a signal
%   Takes in a signal and passes it through a Tapped Delay Line. This
%   mimics the multipath nature of signals through a transmission medium.
%                                                                        
%   sig:    The signal to have the function applied to it
%   chain:  The gains of the taps on the line
%   delay:  The delay length in number of items in the array between each
%           tap

sig = transpose(signal);
chain = transpose(tchain);

delay = 1;

out = [zeros([1 length(sig)]) zeros([1 ((length(chain)-1)*delay)])];
for i = 1:length(chain)
    out = out + [zeros([1 (i-1)]) sig*chain(i) zeros([1 (length(out)-length(sig)-(i-1))])];;
end

out = transpose(out);

end

