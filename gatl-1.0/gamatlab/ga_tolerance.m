function [r] = ga_tolerance(tol)

persistent tolerance

if nargin == 0
    if isempty(tolerance)
        tolerance = 1e-10;
    end
else
    if ~isnumeric(tol) || ~isscalar(tol) || ~isreal(tol) || tol < 0
        error('GAToolbox:InputArgumentsCheck','The round-off error tolerance must be a real positive value.')
    end
    tolerance = double(tol);
end

if nargin == 0 || nargout > 0
    r = tolerance;
end