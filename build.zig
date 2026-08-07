const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.resolveTargetQuery(.{
        .cpu_arch = .wasm32,
        .os_tag = .freestanding,
    });

    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "lib",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/root.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });

    exe.entry = .disabled;

    const web_dir = "web";

    const install_wasm = b.addInstallArtifact(exe, .{
        .dest_dir = .{ .override = .{ .custom = web_dir } },
        .dest_sub_path = "lib.wasm",
    });

    b.getInstallStep().dependOn(&install_wasm.step);

    const angie3d = "angie3d";

    const angie3d_dep = b.dependency(angie3d, .{
        .target = target,
        .optimize = optimize,
    });

    const angie_mod = angie3d_dep.module(angie3d);
    exe.root_module.export_symbol_names = angie_mod.export_symbol_names;

    const install_angie3d_web = b.addInstallDirectory(.{
        .source_dir = angie3d_dep.path("web"),
        .install_dir = .prefix,
        .install_subdir = web_dir,
    });

    b.getInstallStep().dependOn(&install_angie3d_web.step);

    const install_web = b.addInstallDirectory(.{
        .source_dir = b.path("web"),
        .install_dir = .prefix,
        .install_subdir = web_dir,
    });

    b.getInstallStep().dependOn(&install_web.step);

    exe.root_module.addImport(angie3d, angie3d_dep.module(angie3d));
}
