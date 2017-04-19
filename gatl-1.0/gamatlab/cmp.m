function [r] = cmp(m1,m2)

check_binary_operation_argin

operation = str2func([model_name '_cmp']);
try
    r = multivector(operation(m1,m2));
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end