using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Media3D;

namespace DropShadow
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class Window1 : Window
    {
        // 几何3D
        public MeshGeometry3D m_Mg3d;
        public DiffuseMaterial m_DiffMt;

        //Viewport2DVisual3D View2dTo3d_1;

        public Window1()
        {
            InitializeComponent();

            m_Mg3d = new MeshGeometry3D();
            m_DiffMt = new DiffuseMaterial();

            this.Loaded += new RoutedEventHandler(Window_Loaded);
        }

        public void MouseHitTest(object sender, MouseButtonEventArgs args)
        {
            IInputElemen viewport3d;
            Point mousePos = args.GetPosition(viewport3d);
            PointHitTestParameters hitParams = new PointHitTestParameters(mousePos);
            VisualTreeHelper.HitTest(viewport3d, null, ResultCallback, hitParams);
        }

        private void SetImage(Image ImgName, string strPath)
        {
            BitmapImage imageURI = new BitmapImage();
            imageURI.BeginInit();
            imageURI.UriSource = new Uri(strPath, UriKind.Relative);
            imageURI.EndInit();
            ImgName.Source = imageURI;
        }

        private void SetMeshGeometry3D()
        {
            //////////////////////////////////////////////////////////////////////////
            // 定义定点
            Point3D pt3d1 = new Point3D(-1, 1, -1);
            Point3D pt3d2 = new Point3D(-1, -1, -1);
            Point3D pt3d3 = new Point3D(1, -1, -1);
            Point3D pt3d4 = new Point3D(1, 1, -1);

            // 定点序列
            Point3DCollection pt3DCol = new Point3DCollection();
            pt3DCol.Add(pt3d1);
            pt3DCol.Add(pt3d2);
            pt3DCol.Add(pt3d3);
            pt3DCol.Add(pt3d4);
            m_Mg3d.Positions = pt3DCol;

            //////////////////////////////////////////////////////////////////////////
            Point pt1 = new Point(0, 0);
            Point pt2 = new Point(0, 1);
            Point pt3 = new Point(1, 1);
            Point pt4 = new Point(1, 0);

            PointCollection ptCol = new PointCollection();
            ptCol.Add(pt1);
            ptCol.Add(pt2);
            ptCol.Add(pt3);
            ptCol.Add(pt4);
            m_Mg3d.TextureCoordinates = ptCol;

            //////////////////////////////////////////////////////////////////////////

            Int32Collection n32Col = new Int32Collection();
            n32Col.Add(0);
            n32Col.Add(1);
            n32Col.Add(2);
            n32Col.Add(0);
            n32Col.Add(2);
            n32Col.Add(3);
            m_Mg3d.TriangleIndices = n32Col;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            SetImage(image1, "Images/050817goodfeng14.jpg");
            SetImage(image2, "Images/051027nature10.jpg");
            SetImage(image3, "Images/051027nature11.jpg");
            SetImage(image4, "Images/051123Webshots16.jpg");
            SetImage(image5, "Images/050817goodfeng15.jpg");

            // 设置几何3D
            SetMeshGeometry3D();

            //Brush DmtBrh = new SloidBrush("Transparent");
            //m_DiffMt.Brush = DmtBrh;


            View2dTo3d_1.Geometry = m_Mg3d;
            //View2dTo3d_1.Material = m_DiffMt;
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyStates == Keyboard.GetKeyStates(Key.Escape))
                Application.Current.Shutdown();
        }
    }
}
