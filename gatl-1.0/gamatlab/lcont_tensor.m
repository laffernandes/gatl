function [r] = lcont_tensor()

model_name = ga_active_model;

operation = str2func([model_name '_lcont_tensor']);
try
    r = operation();
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end