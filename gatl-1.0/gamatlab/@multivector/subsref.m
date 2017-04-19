function [r] = subsref(m,S)

switch S.type
    case '()'
        r = m(S.subs{:});
    case '{}'
        try
            if isscalar(m)
                r = m.coefficients(m.coefficients~=0);
                r = r(S.subs{:});
            else
                error('GAToolbox:Multivector:InvalidIndexing','Cell array indexing not supported by arrays of multivector objects.')
            end
        catch err
            rethrow(err);
        end
    otherwise
        error('GAToolbox:Multivector:InvalidIndexing','Structure field indexing not supported by multivector objects.')
end