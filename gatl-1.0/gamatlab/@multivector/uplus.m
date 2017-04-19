function [r] = uplus(m)

model_name = model(m);

operation = str2func([model_name '_uplus']);
try
    r = multivector(operation(m));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end