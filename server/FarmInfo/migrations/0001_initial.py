# Generated by Django 4.2.7 on 2023-11-11 07:16

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='LocalWeather',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('HUMD', models.FloatField(null=True, verbose_name='相對濕度')),
                ('TEMP', models.FloatField(null=True, verbose_name='溫度')),
                ('ELEV', models.FloatField(null=True, verbose_name='高度')),
                ('TIME', models.CharField(max_length=50, unique=True, verbose_name='資料觀測時間')),
                ('PRES', models.FloatField(null=True, verbose_name='測站氣壓')),
                ('CITY', models.CharField(max_length=50, verbose_name='縣市')),
            ],
            options={
                'verbose_name': '本地天氣',
                'verbose_name_plural': '本地天氣數據',
            },
        ),
        migrations.CreateModel(
            name='Weather',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('city', models.CharField(max_length=50, verbose_name='縣市')),
                ('month', models.CharField(choices=[('一月', '一月'), ('二月', '二月'), ('三月', '三月'), ('四月', '四月'), ('五月', '五月'), ('六月', '六月'), ('七月', '七月'), ('八月', '八月'), ('九月', '九月'), ('十月', '十月'), ('十一月', '十一月'), ('十二月', '十二月')], max_length=20, unique=True, verbose_name='月份')),
                ('this_month_rainfall_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='This Month Rainfall Level')),
                ('this_month_temperature_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='This Month Temperature Level')),
                ('three_months_rainfall_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='Three Months Rainfall Level')),
                ('three_months_temperature_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='Three Months Temperature Level')),
                ('one_year_rainfall_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='One Year Rainfall Level')),
                ('one_year_temperature_level', models.IntegerField(choices=[(1, '等级 1'), (2, '等级 2'), (3, '等级 3'), (4, '等级 4'), (5, '等级 5')], verbose_name='One Year Temperature Level')),
            ],
            options={
                'verbose_name': '天氣數據',
                'verbose_name_plural': '天氣數據',
            },
        ),
        migrations.CreateModel(
            name='WeatherObservation',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('HUMD', models.FloatField(null=True, verbose_name='相對濕度')),
                ('TEMP', models.FloatField(null=True, verbose_name='溫度')),
                ('ELEV', models.FloatField(null=True, verbose_name='高度')),
                ('TIME', models.CharField(max_length=50, unique=True, verbose_name='資料觀測時間')),
                ('PRES', models.FloatField(null=True, verbose_name='測站氣壓')),
                ('CITY', models.CharField(max_length=50, verbose_name='縣市')),
                ('H_24R', models.FloatField(null=True, verbose_name='日累積雨量')),
            ],
            options={
                'verbose_name': '氣象觀測',
                'verbose_name_plural': '氣象觀測',
            },
        ),
    ]
