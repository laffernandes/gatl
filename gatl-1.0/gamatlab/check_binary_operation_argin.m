if nargin ~= 2
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

if ~(isa(m1,'multivector') || isreal(m1))
    error('GAToolbox:InputArgumentsCheck','The first input argument must be a multivector object or a real scalar value.')
end

if ~(isa(m2,'multivector') || isreal(m2))
    error('GAToolbox:InputArgumentsCheck','The second input argument must be a multivector object or a real scalar value.')
end

if ~isscalar(m1) && ~isscalar(m2) && (ndims(m1) ~= ndims(m2) || numel(m1) ~= numel(m2))
    error('GAToolbox:InputArgumentsCheck','Matrix dimensions must agree.')
end

if isa(m1,'multivector') && isa(m2,'multivector') && ~strcmp(model(m1),model(m2))
	error('GAToolbox:InputArgumentsCheck','The input multivectors are from different geometric algebra models.')
end

if isa(m1,'multivector')
    model_name = model(m1);
    
    if isreal(m2)
        m2 = multivector(m2,model_name);
    end
elseif isa(m2,'multivector')
    model_name = model(m2);
    
    m1 = multivector(m1,model_name);
else
    model_name = ga_active_model;

    m1 = multivector(m1,model_name);
    m2 = multivector(m2,model_name);
end