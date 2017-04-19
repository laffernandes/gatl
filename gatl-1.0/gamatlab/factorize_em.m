function [scalar factors] = factorize_em(m,tol)

check_unary_operation_argin_tol
check_unary_operation_argin_single

operation = str2func([model_name '_factorize_em']);
try
    [scalar factors] = operation(m,tol);
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end

factors = multivector(factors);