function [vargout] = axis_2c(varargin)

% Set some default properties.
face_alpha = 0.25;
face_color = [0.5 0.5 0.5];
grid_steps = 36;

% Set bounds.
bounds = [-1 1 -1 1 -0.0001 2];
if nargin ~= 0
    arg1 = double(varargin{1});
    bounds(1:numel(arg1)) = arg1(:);
end

% Create axis.
if nargout == 0
	axis([bounds varargin{2:end}])
else
	vargout{:} = axis([bounds varargin{2:end}]);
end
set(gca,'UserData','ga2c_axis')

% Label the axis.
% xlabel(ga2latex('\vectorei{1}'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)
% ylabel(ga2latex('\vectorei{2}'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)
% zlabel(ga2latex('\vectorno'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)

% Set axis aspect ratio.
axis equal

% Display box.
box on

% Plot plane ni = 0.
X = [bounds(1) bounds(1) bounds(2) bounds(2)];
Y = [bounds(3) bounds(4) bounds(4) bounds(3)];
Z = [0 0 0 0];
patch('XData',X,'YData',Y,'ZData',Z,'FaceColor',face_color,'FaceAlpha',face_alpha,'Marker','none','LineStyle','none')

% Plot paraboloid.
grid_step = min(bounds(2)-bounds(1),bounds(4)-bounds(3))/grid_steps;

[X Y] = meshgrid(bounds(1):grid_step:bounds(2),bounds(3):grid_step:bounds(4));
Z = X.^2+Y.^2;

paraboloid = surf2patch(X,Y,Z);

out_of_z_upper_bound = (paraboloid.vertices(:,3)>bounds(6));

u = bounds(6);
v = paraboloid.vertices(out_of_z_upper_bound,[1 2])./repmat(sum(paraboloid.vertices(out_of_z_upper_bound,[1 2]).^2,2),[1 2]);
v = atan2(v(:,2),v(:,1));

paraboloid.vertices(out_of_z_upper_bound,1) = sqrt(u)*cos(v);
paraboloid.vertices(out_of_z_upper_bound,2) = sqrt(u)*sin(v);
paraboloid.vertices(out_of_z_upper_bound,3) = u;

patch('FaceColor',face_color,'FaceAlpha',face_alpha,'Marker','none','LineStyle','none',paraboloid)