function [r] = has_even_grade_only(m,tol)

check_unary_operation_argin_tol

operation = str2func([model_name '_has_even_grade_only']);
try
    r = operation(m,tol);
catch err
    switch err.identifier
        case 'MATLAB:UndefinedFunction'
            error('GAToolbox:UndefinedFunction','Geometric algebra model ''%s'' does not implement ''%s'' or it was not compiled.',model_name,mfilename)
        otherwise
            rethrow(err);
    end
end