function [r] = char(m)

check_unary_operation_argin_single

model_name = model(m);

operation = str2func([model_name '_write']);
try
    r = operation(m,get(0,'Format'));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end