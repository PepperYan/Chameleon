(function() {
    'use strict';


    var chameleon_app = angular.module('Chameleon');
    chameleon_app.controller('HardwareCtrl', function($scope,$route, $http) {
        $scope.$route = $route;

        $http({
            method: 'GET',
            url: 'http://172.20.110.228:6060/master/hardware-resources'
        }).then(function successCallback(response) {


            $scope.hardware = response.data.content;
            $scope.quantities = response.data.quantity;
        }, function errorCallback(response) {
            // 请求失败执行代码
        });
    });

    chameleon_app.controller('RuntimeCtrl', function($scope,$rootScope,$http) {
        $http({
            method: 'GET',
            url: 'http://172.20.110.228:6060/master/runtime-resources'
        }).then(function successCallback(response) {
            $scope.runtime = response.data.content;
            // console.log(response.data.content);
            $scope.quantities = response.data.quantity;
            // console.log(response.data.quantity);
            $rootScope.runtime =  $scope.runtime;
        }, function errorCallback(response) {
            // 请求失败执行代码
        });
    });

    chameleon_app.controller('SlaveCtrl', function($scope,$rootScope, $http,$routeParams) {
        $scope.slave_uuid = $routeParams.slave_uuid;
        $scope.slave_id = $routeParams.slave_id;
        $scope.cpu_used = $routeParams.cpu_used;
        $scope.mem_used = $routeParams.mem_used;
        $scope.disk_used = $routeParams.disk_used;

        // 基于准备好的dom，初始化echarts实例
        var myChart = echarts.init(document.getElementById('cpu'));

        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption({
            title: {
                text: 'cpu使用率',
                x:'center'
            },
            tooltip : {
                trigger: 'item',
                formatter: "{a} <br/>{b} :  ({d}%)"
            },
            legend: {
                orient: 'vertical',
                left: 'right',
                data: ['已使用','未使用']
            },
            series : [
                {
                    name: 'cpu使用率',
                    type: 'pie',
                    radius: '55%',
                    label: {
                        normal: {
                            formatter: '  {b|{b}：}  {per|{d}%}  ',
                            backgroundColor: '#eee',
                            borderColor: '#aaa',
                            borderWidth: 1,
                            borderRadius: 4,
                            // shadowBlur:3,
                            // shadowOffsetX: 2,
                            // shadowOffsetY: 2,
                            // shadowColor: '#999',
                            // padding: [0, 7],
                            rich: {
                                a: {
                                    color: '#999',
                                    lineHeight: 22,
                                    align: 'center'
                                },
                                // abg: {
                                //     backgroundColor: '#333',
                                //     width: '100%',
                                //     align: 'right',
                                //     height: 22,
                                //     borderRadius: [4, 4, 0, 0]
                                // },
                                hr: {
                                    borderColor: '#aaa',
                                    width: '100%',
                                    borderWidth: 0.5,
                                    height: 0
                                },
                                b: {
                                    fontSize: 16,
                                    lineHeight: 33
                                },
                                per: {
                                    color: '#eee',
                                    backgroundColor: '#334455',
                                    padding: [2, 4],
                                    borderRadius: 2
                                }
                            }
                        }
                    },
                    center: ['50%', '60%'],
                    data:[
                        {value:$scope.cpu_used, name:'已使用'},
                        {value:100-$scope.cpu_used, name:'未使用'},
                    ],
                    itemStyle: {
                        emphasis: {
                            shadowBlur: 10,
                            shadowOffsetX: 0,
                            shadowColor: 'rgba(0, 0, 0, 0.5)'
                        }
                    }

                }
            ]
        })

        var myChart = echarts.init(document.getElementById('mem'));

        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption({
            title: {
                text: 'mem使用率',
                x:'center'
            },
            tooltip : {
                trigger: 'item',
                formatter: "{a} <br/>{b} :  ({d}%)"
            },
            legend: {
                orient: 'vertical',
                left: 'right',
                data: ['已使用','未使用']
            },
            series : [
                {
                    name: 'mem使用率',
                    type: 'pie',
                    radius: '55%',
                    label: {
                        normal: {
                            formatter: '  {b|{b}：}  {per|{d}%}  ',
                            backgroundColor: '#eee',
                            borderColor: '#aaa',
                            borderWidth: 1,
                            borderRadius: 4,
                            // shadowBlur:3,
                            // shadowOffsetX: 2,
                            // shadowOffsetY: 2,
                            // shadowColor: '#999',
                            // padding: [0, 7],
                            rich: {
                                a: {
                                    color: '#999',
                                    lineHeight: 22,
                                    align: 'center'
                                },
                                // abg: {
                                //     backgroundColor: '#333',
                                //     width: '100%',
                                //     align: 'right',
                                //     height: 22,
                                //     borderRadius: [4, 4, 0, 0]
                                // },
                                hr: {
                                    borderColor: '#aaa',
                                    width: '100%',
                                    borderWidth: 0.5,
                                    height: 0
                                },
                                b: {
                                    fontSize: 16,
                                    lineHeight: 33
                                },
                                per: {
                                    color: '#eee',
                                    backgroundColor: '#334455',
                                    padding: [2, 4],
                                    borderRadius: 2
                                }
                            }
                        }
                    },
                    center: ['50%', '60%'],
                    data:[
                        {value:$scope.mem_used, name:'已使用'},
                        {value:100-$scope.mem_used, name:'未使用'},
                    ],
                    itemStyle: {
                        emphasis: {
                            shadowBlur: 10,
                            shadowOffsetX: 0,
                            shadowColor: 'rgba(0, 0, 0, 0.5)'
                        }
                    }

                }
            ]
        })

        var myChart = echarts.init(document.getElementById('disk'));

        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption({
            title: {
                text: 'disk使用率',
                x:'center'
            },
            tooltip : {
                trigger: 'item',
                formatter: "{a} <br/>{b} :  ({d}%)"
            },
            legend: {
                orient: 'vertical',
                left: 'right',
                data: ['已使用','未使用']
            },
            series : [
                {
                    name: 'disk使用率',
                    type: 'pie',
                    radius: '55%',
                    label: {
                        normal: {
                            formatter: '  {b|{b}：}  {per|{d}%}  ',
                            backgroundColor: '#eee',
                            borderColor: '#aaa',
                            borderWidth: 1,
                            borderRadius: 4,
                            // shadowBlur:3,
                            // shadowOffsetX: 2,
                            // shadowOffsetY: 2,
                            // shadowColor: '#999',
                            // padding: [0, 7],
                            rich: {
                                a: {
                                    color: '#999',
                                    lineHeight: 22,
                                    align: 'center'
                                },
                                // abg: {
                                //     backgroundColor: '#333',
                                //     width: '100%',
                                //     align: 'right',
                                //     height: 22,
                                //     borderRadius: [4, 4, 0, 0]
                                // },
                                hr: {
                                    borderColor: '#aaa',
                                    width: '100%',
                                    borderWidth: 0.5,
                                    height: 0
                                },
                                b: {
                                    fontSize: 16,
                                    lineHeight: 33
                                },
                                per: {
                                    color: '#eee',
                                    backgroundColor: '#334455',
                                    padding: [2, 4],
                                    borderRadius: 2
                                }
                            }
                        }
                    },
                    center: ['50%', '60%'],
                    data:[
                        {value:$scope.disk_used, name:'已使用'},
                        {value:100-$scope.disk_used, name:'未使用'},
                    ],
                    itemStyle: {
                        emphasis: {
                            shadowBlur: 10,
                            shadowOffsetX: 0,
                            shadowColor: 'rgba(0, 0, 0, 0.5)'
                        }
                    }

                }
            ]
        })

        var myChart = echarts.init(document.getElementById('swap'));

        // 使用刚指定的配置项和数据显示图表。
        myChart.setOption({
            title: {
                text: 'swap使用率',
                x:'center'
            },
            tooltip : {
                trigger: 'item',
                formatter: "{a} <br/>{b} :  ({d}%)"
            },
            legend: {
                orient: 'vertical',
                left: 'right',
                data: ['已使用','未使用']
            },
            series : [
                {
                    name: 'swap使用率',
                    type: 'pie',
                    radius: '55%',
                    label: {
                        normal: {
                            formatter: '  {b|{b}：}  {per|{d}%}  ',
                            backgroundColor: '#eee',
                            borderColor: '#aaa',
                            borderWidth: 1,
                            borderRadius: 4,
                            // shadowBlur:3,
                            // shadowOffsetX: 2,
                            // shadowOffsetY: 2,
                            // shadowColor: '#999',
                            // padding: [0, 7],
                            rich: {
                                a: {
                                    color: '#999',
                                    lineHeight: 22,
                                    align: 'center'
                                },
                                // abg: {
                                //     backgroundColor: '#333',
                                //     width: '100%',
                                //     align: 'right',
                                //     height: 22,
                                //     borderRadius: [4, 4, 0, 0]
                                // },
                                hr: {
                                    borderColor: '#aaa',
                                    width: '100%',
                                    borderWidth: 0.5,
                                    height: 0
                                },
                                b: {
                                    fontSize: 16,
                                    lineHeight: 33
                                },
                                per: {
                                    color: '#eee',
                                    backgroundColor: '#334455',
                                    padding: [2, 4],
                                    borderRadius: 2
                                }
                            }
                        }
                    },
                    center: ['50%', '60%'],
                    data:[
                        {value:$scope.cpu_used, name:'已使用'},
                        {value:100-$scope.cpu_used, name:'未使用'},
                    ],
                    itemStyle: {
                        emphasis: {
                            shadowBlur: 10,
                            shadowOffsetX: 0,
                            shadowColor: 'rgba(0, 0, 0, 0.5)'
                        }
                    }

                }
            ]
        })




        console.log("40  "+ $scope.slave_uuid);
        console.log( $scope.slave_id );
        console.log($scope.cpu_used);
        console.log($scope.mem_used);

    });


    chameleon_app.controller('TopologyCtrl', function($scope, $http) {
        $http({
            method: 'GET',
            url: 'http://172.20.110.228:6060/master/runtime-resources'
        }).then(function successCallback(response) {
            $scope.runtime = response.data.content;
            // console.log(response.data.content);
            $scope.quantities = response.data.quantity;
            // console.log(response.data.quantity);

            var DIR = '../icon/refresh-cl/';
            var vertexes = new Array();

            var my_master = {};
            vertexes[0] = my_master;
            my_master.id = 0;
            my_master.label = "master";
            my_master.shape = 'image';
            my_master.image = DIR + 'Hardware-WQN-main.png';
            my_master.title = '主节点';

            //my_slaves[0] = my_master;
            var index_slave = 1;
            var index_edge = -1;
            var my_edges = [];
            var cur_index=0;

            if($scope.quantities>=2){
                my_edges = [];
                for(var i in $scope.runtime){
                    var slave = $scope.runtime[i];

                    var temp_slave = {}; // 添加一个顶点
                    cur_index++; // 全局id
                    temp_slave.label = "slave"+cur_index;
                    // console.log('57 '+cur_index);
                    temp_slave.id = cur_index;
                    temp_slave.shape ='image';
                    temp_slave.image = DIR + 'Hardware-WQN-server.png';
                    temp_slave.title = $scope.runtime[i].slave_id;
                    vertexes[cur_index]= temp_slave; // cur_index 同时代表 顶点集合 my_slaves 的下标
                    // console.info(vertexes);
                    var temp_edge = {}; // 添加一条边 master -> temp_slave
                    temp_edge.from = 0;
                    temp_edge.to = temp_slave.id;
                    temp_edge.arrows = 'to';
                    temp_edge.label = Math.round($scope.runtime[i].net_usage.net_used*100)/100+'KiB/s';
                    index_edge++; // 边集合 my_edges 的下标
                    my_edges[index_edge] = temp_edge;

                    // 添加cpu节点
                    var temp_cpu = {};
                    cur_index++;
                    temp_cpu.label = "cpu";
                    temp_cpu.id = cur_index;
                    temp_cpu.group = 'server';
                    temp_cpu.title = Math.round($scope.runtime[i].cpu_usage.cpu_used);
                    temp_cpu.value = Math.ceil(Math.round($scope.runtime[i].cpu_usage.cpu_used)/10);
                    vertexes[cur_index] = temp_cpu;
                    // 添加连接cpu节点的边, temp_slave -> temp_cpu
                    var edge_cpu = {};
                    index_edge++;
                    edge_cpu.from= temp_slave.id;
                    edge_cpu.to = temp_cpu.id;
                    edge_cpu.arrows = 'to';
                    my_edges[index_edge] = edge_cpu;

                    // 添加disk节点
                    var temp_disk = {};
                    cur_index++;
                    temp_disk.label = "disk";
                    temp_disk.id = cur_index;
                    temp_disk.group = 'switch';
                    temp_disk.title = Math.round(100-$scope.runtime[i].disk_usage.available_percent);
                    temp_disk.value = Math.ceil(Math.round(100-$scope.runtime[i].disk_usage.available_percent)/10);
                    vertexes[cur_index] = temp_disk;
                    // 添加连接cpu节点的边, temp_slave -> temp_cpu
                    var edge_disk = {};
                    index_edge++;
                    edge_disk.from= temp_slave.id;
                    edge_disk.to = temp_disk.id;
                    edge_disk.arrows = 'to';
                    my_edges[index_edge] = edge_disk;

                    // 添加mem节点
                    var temp_mem = {};
                    cur_index++;
                    temp_mem.label = "mem";
                    temp_mem.id = cur_index;
                    temp_mem.group = 'desktop';
                    temp_mem.title = Math.round($scope.runtime[i].mem_usage.mem_available / $scope.runtime[i].mem_usage.mem_total * 100);
                    temp_mem.value = Math.ceil(Math.round($scope.runtime[i].mem_usage.mem_available / $scope.runtime[i].mem_usage.mem_total * 100)/10);
                    vertexes[cur_index] = temp_mem;
                    // 添加连接mem节点的边, temp_slave -> temp_mem
                    var edge_mem = {};
                    index_edge++;
                    edge_mem.from= temp_slave.id;
                    edge_mem.to = temp_mem.id;
                    edge_mem.arrows = 'to';
                    my_edges[index_edge] = edge_mem;

                    // 添加swap节点
                    var temp_swap = {};
                    cur_index++;
                    temp_swap.label = "swap";
                    temp_swap.id = cur_index;
                    temp_swap.group = 'mobile';
                    temp_swap.title = $scope.runtime[i].mem_usage.swap_free / $scope.runtime[i].mem_usage.swap_total * 100;
                    vertexes[cur_index] = temp_swap;
                    // 添加连接net节点的边, temp_slave -> temp_net
                    var edge_swap = {};
                    index_edge++;
                    edge_swap.from= temp_slave.id;
                    edge_swap.to = temp_swap.id;
                    edge_swap.arrows = 'to';
                    my_edges[index_edge] = edge_swap;


                }
            }else{
                my_edges=[];
            }


            var nodes = new vis.DataSet(vertexes);


            var edges = new vis.DataSet(my_edges);

            var container = document.getElementById('mynetwork');
            var data = {
                nodes: nodes,
                edges: edges
            };

            var options = {
                interaction: {
                    navigationButtons: true,
                    keyboard: true
                },
                groups: {
                    'switch': {
                        shape: 'dot',
                        color: '#FF9900' // orange
                    },
                    desktop: {
                        shape: 'dot',
                        color: "#109618" // green
                    },
                    mobile: {
                        shape: 'dot',
                        color: "#5A1E5C" // purple
                    },
                    server: {
                        shape: 'dot',
                        color: "#c53c3d" // red
                    },
                    internet: {
                        shape: 'square',
                        color: "#0c58c5" // blue
                    }
                }

            };

            var network = new vis.Network(container, data, options);

            // add event listeners
            network.on('select', function(params) {
                document.getElementById('selection').innerHTML = 'Selection: ' + params.nodes;
            });

        }, function errorCallback(response) {
            // 请求失败执行代码
        });
    });


})();