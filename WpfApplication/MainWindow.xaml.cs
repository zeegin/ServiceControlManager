using System; 
using System.Windows;
using System.Windows.Controls;
using System.IO;
using InstDrv;

namespace WpfApplication
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void openFileDialogButton_Click(object sender, RoutedEventArgs e)
        {
            using (System.Windows.Forms.OpenFileDialog fd = new System.Windows.Forms.OpenFileDialog())
            {
                fd.Filter = "Драйвер (*.sys)|*.sys|Все файлы (*.*)|*.*";
                fd.FilterIndex = 1;
                if (fd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    try
                    {
                        using (StreamReader fs = new StreamReader(fd.FileName))
                        {
                            fs.Close();
                        }
                        filePathTextBox.Text = fd.FileName;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
            }
        }

        private void addDriverButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (ServiceControlManager scm = new ServiceControlManager())
                {
                    scm.AddDriver(serviceNameTextBox.Text, filePathTextBox.Text);
                }
                MessageBox.Show("Драйвер добавлен");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void deleteDriverButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (ServiceControlManager scm = new ServiceControlManager())
                {
                    scm.DeleteDriver(serviceNameTextBox.Text);
                }
                MessageBox.Show("Драйвер удален или помечен на удаление");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void startDriverButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (ServiceControlManager scm = new ServiceControlManager())
                {
                    scm.StartDriver(serviceNameTextBox.Text);
                }
                MessageBox.Show("Драйвер запущен");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void stopDriverButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using(ServiceControlManager scm = new ServiceControlManager())
                {
                    scm.StopDriver(serviceNameTextBox.Text);
                }
                MessageBox.Show("Драйвер остановлен");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
