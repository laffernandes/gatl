function [r] = has_grade(k,m,tol)

if ~((nargin == 2) || (nargin == 3))
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

if ~isnumeric(k) || ~isscalar(k) || any(k ~= fix(k))
    error('GAToolbox:InputArgumentsCheck','The first input argument must be a single integer value.')
end
k = int32(k);

if ~(isa(m,'multivector') || isreal(m))
    error('GAToolbox:InputArgumentsCheck','The second input argument must be a multivector object or a real scalar value.')
end

if isa(m,'multivector')
    model_name = model(m);
else
    model_name = ga_active_model;
    m = multivector(m,model_name);
end

if nargin == 2
    tol = ga_tolerance;
elseif ~(isscalar(tol) && isreal(tol))
	error('GAToolbox:InputArgumentsCheck','The assumed tolerance must be a real scalar value.')
end

operation = str2func([model_name '_has_grade']);
try
    r = operation(k,m,tol);
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end