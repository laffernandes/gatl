function [r] = multivector(m,model)

model_name = ga_active_model;

try
    if nargin == 0
        scalar = str2func([model_name '_scalar']);
        r = class(scalar(0),'multivector');
    elseif nargin == 1
        if isstruct(m)
            r = class(m,'multivector');
        elseif isa(m,'multivector')
            r = m;
        elseif isreal(m)
            scalar = str2func([model_name '_scalar']);
            r = class(scalar(double(m)),'multivector');
        else
            error('GAToolbox:InputArgumentsCheck','The input argument must be a multivector object or a real scalar value.')
        end
    else
        if isreal(m)
            scalar = str2func([char(model) '_scalar']);
            r = class(scalar(double(m)),'multivector');
        else
            error('GAToolbox:InputArgumentsCheck','The input arguments must be a real scalar value and a model name.')
        end
    end
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''scalar'' or it was not compiled.',model_name)
        otherwise
            rethrow(err);
    end
end