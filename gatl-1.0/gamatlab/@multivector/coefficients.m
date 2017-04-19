function [r] = coefficients(m)

if isscalar(m)
    r = m.coefficients;
else
    r = cell(size(m));
    r(:) = {m.coefficients};
end