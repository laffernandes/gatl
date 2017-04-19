if nargin == 0
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

n = numel(varargin{1});
for i=2:nargin
    if n ~= numel(varargin{i})
        error('GAToolbox:InputArgumentsCheck','Coordinate vectors must be the same lengths.')
    end
end

coords = zeros(n,nargin);
for i=1:nargin
    coord = varargin{i}(:);
    if ~isreal(coord)
        error('GAToolbox:InputArgumentsCheck','Coordinate vectors must be real type values.')
    end
    
    coords(:,i) = coord;
end

model_name = ga_active_model;