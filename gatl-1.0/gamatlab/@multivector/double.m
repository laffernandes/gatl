function [r] = double(m)

if all(is_scalar(m))
    r = zeros(size(m));
    parfor i=1:numel(m)
        r(i) = m(i).coefficients(1);
    end
else
    error('GAToolbox:Multivector:InvalidCast','Invalid cast from multivector object to scalar value.')
end