function [r] = interpret(m,tol)

check_unary_operation_argin_tol

operation = str2func([model_name '_interpret']);
try
    r = operation(m,tol);
    
    if isscalar(r)
        r = r{:};
    end
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end