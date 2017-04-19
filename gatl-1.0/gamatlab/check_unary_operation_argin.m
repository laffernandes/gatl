if nargin ~= 1
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