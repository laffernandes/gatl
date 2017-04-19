function [r] = model(m)

models = unique(char(m(:).model),'rows');
switch size(models,1)
    case 1, r = models;
    case 0, r = ga_active_model();
    otherwise, error('GAToolbox:MixedModels','Mixed geometric aglebra models.')
end