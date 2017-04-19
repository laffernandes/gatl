function [r i j] = unique(m)

if ~isscalar(unique({m(:).model}))
    error('GAToolbox:MixedModels','Mixed geometric aglebra models.')
end

[dummy i j] = unique(cell2mat({m(:).coefficients}'),'rows');
r = m(i);

if isvector(m) && (size(m,2) > 1)
    i = i';
    j = j';
end