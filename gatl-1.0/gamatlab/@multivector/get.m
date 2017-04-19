function [r] = get(m,property_name)

% Check input arguments.
if nargin ~= 2
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

% Return the requested property.
switch lower(char(property_name))
    case 'model'
        if isscalar(m)
            r = m.model;
        else
            r = cell(size(m));
            r(:) = {m.model};
        end
    case 'coefficients'
        if isscalar(m)
            r = m.coefficients;
        else
            r = cell(size(m));
            r(:) = {m.coefficients};
        end
    otherwise
        error('GAToolbox:Multivector:UnknownProperty','Unknown property name ''%s''.',property_name)
end