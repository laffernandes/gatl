if ~((nargin == 1) || (nargin == 2))
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

if ~(isa(m,'multivector') || isreal(m))
    error('GAToolbox:InputArgumentsCheck','The input argument must be a multivector object or a real scalar value.')
end

if isa(m,'multivector')
    model_name = model(m);
else
    model_name = ga_active_model;
    m = multivector(m,model_name);
end

if nargin == 1
    tol = ga_tolerance;
elseif ~(isscalar(tol) && isreal(tol))
	error('GAToolbox:InputArgumentsCheck','The assumed tolerance must be a real scalar value.')
end